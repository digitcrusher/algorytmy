/*
 * Algorytm Aho-Corasick - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"

/*
 * Algorytm Aho-Corasick -
 *   Struktura danych pozwalająca na znalezienie wszystkich wystąpień kluczy
 *   w słowie o długości n w O(n + w), gdzie w to liczba pasujących przedziałów.
 */
template<int alpha_size, class AlphaToNum>
struct AhoCorasick {
  AlphaToNum alpha_to_num;

  struct Node {
    AhoCorasick &dict;

    array<Node*, alpha_size> children;
    vector<int> keys;

    Node *parent = nullptr;
    char prev_char;
    int depth = 0;

    Node *_fail = nullptr, *_exit = nullptr;

    Node(AhoCorasick &dict): dict(dict), children({}) {}
    Node(AhoCorasick &dict, Node *parent, char prev_char):
      dict(dict), children({}),
      parent(parent), prev_char(prev_char), depth(parent->depth + 1) {}

    Node*& child(char c) {
      return children[dict.alpha_to_num(c)];
    }

    Node* next(char c) {
      auto result = this;
      while(result->fail() != result && result->child(c) == nullptr) {
        result = result->fail();
      }
      if(result->child(c) != nullptr) {
        result = result->child(c);
      }
      return result;
    }

    Node* fail() {
      if(_fail == nullptr) {
        _fail = parent->fail();
        if(_fail != parent) {
          _fail = _fail->next(prev_char);
        }
      }
      return _fail;
    }

    Node* exit() {
      if(_exit == nullptr) {
        _exit = fail();
        if(_exit->keys.empty()) {
          _exit = _exit->exit();
        }
      }
      return _exit;
    }
  };
  Node root;
  int keyc;
  vector<int> key_repr;

  AhoCorasick(vector<string> const& keys, AlphaToNum alpha_to_num = {}):
    root(*this), keyc(keys.size()), key_repr(keyc), alpha_to_num(alpha_to_num)
  {
    root._fail = &root;
    for(auto i: v::iota(0, keyc)) {
      auto node = &root;
      for(auto c: keys[i]) {
        auto &child = node->child(c);
        if(child == nullptr) {
          child = new Node(*this, node, c);
        }
        node = child;
      }
      node->keys.push_back(i);
      key_repr[i] = node->keys.front();
    }
  }

  ~AhoCorasick() {
    auto purge = Y([&](auto &self, Node *node) -> void {
      for(auto child: node->children | v::filter(λ(_ != nullptr))) {
        self(child);
        delete child;
      }
    });
    purge(&root);
  }

  void match_in(string const& str, auto on_match) {
    auto node = &root;
    for(auto i: v::iota(0, (int) str.size())) {
      node = node->next(str[i]);
      auto suffix = node;
      while(true) {
        if(!suffix->keys.empty()) {
          on_match(i - suffix->depth + 1, i, suffix->keys);
        }
        if(suffix->exit() == suffix) break;
        suffix = suffix->exit();
      }
    }
  }

  vector<int> find_in(string const& str) {
    vector result(keyc, -1);

    match_in(str, [&](int l, int r, vector<int> const& keys) {
      if(result[keys.front()] == -1) {
        result[keys.front()] = l;
      }
    });
    for(auto i: v::iota(0, keyc)) {
      result[i] = result[key_repr[i]];
    }

    return result;
  }

  vector<int> count_in(string const& str) {
    vector result(keyc, 0);

    match_in(str, [&](int l, int r, vector<int> const& keys) {
      result[keys.front()]++;
    });
    for(auto i: v::iota(0, keyc)) {
      result[i] = result[key_repr[i]];
    }

    return result;
  }
};
