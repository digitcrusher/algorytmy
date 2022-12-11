/*
 * Skompresowane drzewo trie - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <array>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

/*
 * Skompresowane drzewo trie -
 *   Słownik z kluczem typu string wspierający operacje odnalezienia (get, has),
 *   ustawienia wartości (set) lub usunięcia klucza (erase) w O(k), gdzie k to
 *   długość klucza, oraz zwrócenia listy kluczy w kolejności alfabetu (keys) w
 *   O(n). Zużywa O(a * n) pamięci, gdzie a to rozmiar alfabetu.
 *
 * AlphaToNum: char -> int
 *   Przypisuje każdemu znakowi z alfabetu unikalną liczbę w [0, alpha_size).
 * NumToAlpha: int -> char
 *   Funkcja odwrotna do AlphaToNum.
 */
template<class Value, int alpha_size, class AlphaToNum, class NumToAlpha>
struct CompressedTrie {
  AlphaToNum alpha_to_num;
  NumToAlpha num_to_alpha;

  struct Node {
    Value val;
    array<Node*, alpha_size> children;
    array<string, alpha_size> labels;
    int childc = 0;
    bool has_val = false;

    Node(): children({}) {}
    Node(Value val): children({}), val(val), has_val(true) {}
  };

  Node root;

  CompressedTrie(AlphaToNum alpha_to_num = AlphaToNum(),
                 NumToAlpha num_to_alpha = NumToAlpha()):
    alpha_to_num(alpha_to_num), num_to_alpha(num_to_alpha) {}

  ~CompressedTrie() {
    function<void(Node*)> dfs = [&](Node *node) {
      for(int i = 0; i < alpha_size; i++) {
        Node *child = node->children[i];
        if(child != nullptr) {
          dfs(child);
          delete child;
        }
      }
    };
    dfs(&root);
  }

  Node* find(string key) {
    Node *node = &root;
    int i = 0;
    while(i < key.size()) {
      int first = alpha_to_num(key[i]);
      i++;
      Node *&child = node->children[first];
      string &label = node->labels[first];

      if(child == nullptr) {
        return nullptr;
      } else {
        int j = 0;
        while(i < key.size() && j < label.size() && key[i] == label[j]) {
          i++, j++;
        }

        if(j == label.size()) {
          node = child;
        } else {
          return nullptr;
        }
      }
    }
    return node;
  }
  Value get(string key) {
    Node *node = find(key);
    if(node != nullptr && node->has_val) {
      return node->val;
    } else {
      throw std::runtime_error("Nie odnaleziono klucza w drzewie.");
    }
  }
  bool has(string key) {
    Node *node = find(key);
    return node != nullptr && node->has_val;
  }

  void set(string key, Value val) {
    Node *node = &root;
    int i = 0;
    while(i < key.size()) {
      int first = alpha_to_num(key[i]);
      i++;
      Node *&child = node->children[first];
      string &label = node->labels[first];

      if(child == nullptr) {
        node->childc++;
        child = new Node(val);
        label = key.substr(i);
        return;
      } else {
        int j = 0;
        while(i < key.size() && j < label.size() && key[i] == label[j]) {
          i++, j++;
        }

        if(j == label.size()) {
          node = child;
        } else {
          Node *fork = new Node;

          if(i == key.size()) {
            fork->val = val;
            fork->has_val = true;
          } else {
            fork->childc++;
            fork->children[alpha_to_num(key[i])] = new Node(val);
            fork->labels[alpha_to_num(key[i])] = key.substr(i + 1);
          }

          fork->childc++;
          fork->children[alpha_to_num(label[j])] = child;
          fork->labels[alpha_to_num(label[j])] = label.substr(j + 1);

          child = fork;
          label.resize(j);
          return;
        }
      }
    }
    node->val = val;
    node->has_val = true;
  }
  bool erase(string key) {
    Node *node = &root, *parent = nullptr, *grandparent = nullptr;
    int i = 0;
    while(i < key.size()) {
      int first = alpha_to_num(key[i]);
      i++;
      Node *&child = node->children[first];
      string &label = node->labels[first];

      if(child == nullptr) {
        return false;
      } else {
        int j = 0;
        while(i < key.size() && j < label.size() && key[i] == label[j]) {
          i++, j++;
        }

        if(j == label.size()) {
          grandparent = parent;
          parent = node;
          node = child;
        } else {
          return false;
        }
      }
    }
    if(!node->has_val) {
      return false;
    }
    node->has_val = false;
    if(parent != nullptr) {
      int node_first = 0;
      while(parent->children[node_first] != node) {
        node_first++;
      }

      if(node->childc == 0) {
        // Usuwamy pusty wierzchołek, który jest liściem.
        parent->childc--;
        parent->children[node_first] = nullptr;
        parent->labels[node_first].clear();
        delete node;

        if(!parent->has_val && parent->childc == 1 && grandparent != nullptr) {
          // Scalamy pustego rodzica wierzchołka z jedynym rodzeństwem wierzchołka.
          int parent_first = 0;
          while(grandparent->children[parent_first] != parent) {
            parent_first++;
          }
          int sibling_first = 0;
          while(parent->children[sibling_first] == nullptr) {
            sibling_first++;
          }
          Node *sibling = parent->children[sibling_first];

          grandparent->children[parent_first] = sibling;
          grandparent->labels[parent_first].push_back(num_to_alpha(sibling_first));
          grandparent->labels[parent_first] += parent->labels[sibling_first];
          delete parent;
        }
      } else if(node->childc == 1) {
        // Scalamy pusty wierzchołek z jego jedynym dzieckiem.
        int child_first = 0;
        while(node->children[child_first] == nullptr) {
          child_first++;
        }
        Node *child = node->children[child_first];

        parent->children[node_first] = child;
        parent->labels[node_first].push_back(num_to_alpha(child_first));
        parent->labels[node_first] += node->labels[child_first];
        delete node;
      }
    }
    return true;
  }

  vector<string> keys() {
    vector<string> result;

    string key;
    function<void(Node*)> dfs = [&](Node *node) {
      if(node->has_val) {
        result.push_back(key);
      }
      for(int i = 0; i < alpha_size; i++) {
        if(node->children[i] != nullptr) {
          key.push_back(num_to_alpha(i));
          key += node->labels[i];
          dfs(node->children[i]);
          key.resize(key.size() - 1 - node->labels[i].size());
        }
      }
    };
    dfs(&root);

    return result;
  }
};
