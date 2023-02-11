/*
 * Binary lifting - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/int.hpp"
#include <climits>
#include <functional>
#include <vector>

/*
 * Binary lifting -
 *   Generuje strukturę z drzewa ukorzenionego w O(V) pozwalającą na
 *   wyszukiwanie binarne na ścieżce z dowolnego wierzchołka do korzenia
 *   w O(log d), gdzie d to długość ścieżki.
 */
vector<int> binary_lift(vector<int> const& parent) {
  int const n = parent.size();

  vector<int> lift(n, -1);

  vector<int> depth(n);
  function<void(int)> calc = [&](int node) {
    if(parent[node] == -1) {
      lift[node] = node;
      depth[node] = 0;
      return;
    }
    if(lift[parent[node]] == -1) {
      calc(parent[node]);
    }
    depth[node] = depth[parent[node]] + 1;
    int p = parent[node];
    if(depth[p] - depth[lift[p]] == depth[lift[p]] - depth[lift[lift[p]]]) {
      lift[node] = lift[lift[p]];
    } else {
      lift[node] = p;
    }
  };
  for(int i = 0; i < n; i++) {
    if(lift[i] == -1) {
      calc(i);
    }
  }
  return lift;
}

/*
 * Znajduje ostatni wierzchołek na ścieżce z wierzchołka do korzenia
 * w O(log d), gdzie d to długość ścieżki, spełniający dowolny warunek
 * monotoniczny nierosnący (jak wiadomo, true to 1, a false to 0) lub -1,
 * jeśli taki wierzchołek nie istnieje.
 */
template<class Predicate>
int lifting_find_last(vector<int> const& parent, vector<int> const& lift,
                      int node, Predicate pred = Predicate())
{
  int const n = lift.size();

  if(!pred(node)) {
    return -1;
  }

  while(parent[node] != -1 && pred(parent[node])) {
    if(pred(lift[node])) {
      node = lift[node];
    } else {
      node = parent[node];
    }
  }
  return node;
}

/*
 * Znajduje pierwszy wierzchołek na ścieżce z wierzchołka do korzenia
 * w O(log d), gdzie d to długość ścieżki, spełniający dowolny warunek
 * monotoniczny niemalejący (jak wiadomo, true to 1, a false to 0) lub -1,
 * jeśli taki wierzchołek nie istnieje.
 */
template<class Predicate>
int lifting_find_first(vector<int> const& parent, vector<int> const& lift,
                       int node, Predicate pred = Predicate())
{
  int const n = lift.size();

  if(pred(node)) {
    return node;
  }

  while(parent[node] != -1 && !pred(parent[node])) {
    if(!pred(lift[node])) {
      node = lift[node];
    } else {
      node = parent[node];
    }
  }
  return parent[node] == -1 ? -1 : parent[node];
}

/*
 * Gorszy binary lifting -
 *   Generuje strukturę z drzewa ukorzenionego w O(V log V) pozwalającą na
 *   wyszukiwanie binarne na ścieżce z dowolnego wierzchołka do korzenia
 *   w O(log d), gdzie d to długość ścieżki. Mimo trzykrotnie mniejszej liczby
 *   skoków niz zwykły jest wciąż wolniejszy, a mimo to popularniejszy.
 */
vector<vector<int>> worse_binary_lift(vector<int> const& parent) {
  int const n = parent.size();

  vector<vector<int>> lift(n);

  function<void(int)> calc = [&](int node) {
    if(parent[node] == -1) return;
    if(lift[parent[node]].empty()) {
      calc(parent[node]);
    }
    lift[node].push_back(parent[node]);
    for(int i = 0; i < lift[lift[node][i]].size(); i++) {
      lift[node].push_back(lift[lift[node][i]][i]);
    }
  };
  for(int i = 0; i < n; i++) {
    if(lift[i].empty()) {
      calc(i);
    }
  }
  return lift;
}

/*
 * Lżejszy gorszy binary lifting -
 *   Generuje strukturę z drzewa ukorzenionego w O(V log V) pozwalającą na
 *   wyszukiwanie binarne na ścieżce z dowolnego wierzchołka do korzenia
 *   w O(log d), gdzie d to długość ścieżki, ale z mniejszą stała pamięciową
 *   i większą stałą czasową niż zwykły gorszy binary lifting.
 */
vector<vector<int>> worse_binary_lift_light(vector<int> const& parent) {
  int const n = parent.size();

  vector<vector<int>> lift(n);

  vector<int> depth(n);
  function<void(int)> calc = [&](int node) {
    if(parent[node] == -1) {
      depth[node] = 0;
      return;
    }
    if(lift[parent[node]].empty()) {
      calc(parent[node]);
    }
    depth[node] = depth[parent[node]] + 1;
    lift[node].push_back(parent[node]);
    for(int i = 0; i < countr_zero(depth[node]) && i < lift[lift[node][i]].size(); i++) {
      lift[node].push_back(lift[lift[node][i]][i]);
    }
  };
  for(int i = 0; i < n; i++) {
    if(lift[i].empty()) {
      calc(i);
    }
  }
  return lift;
}

/*
 * Znajduje ostatni wierzchołek na ścieżce z wierzchołka do korzenia
 * w O(log d), gdzie d to długość ścieżki, spełniający dowolny warunek
 * monotoniczny nierosnący (jak wiadomo, true to 1, a false to 0) lub -1,
 * jeśli taki wierzchołek nie istnieje.
 */
template<class Predicate>
int worse_lifting_find_last(vector<vector<int>> const& lift,
                      int node, Predicate pred = Predicate())
{
  int const n = lift.size();

  if(!pred(node)) {
    return -1;
  }

  int max_jump = INT_MAX;
  while(!lift[node].empty() && pred(lift[node][0])) {
    int jump = min(max_jump, (int) lift[node].size() - 1);
    while(!pred(lift[node][jump])) {
      jump--;
      max_jump = jump;
    }
    node = lift[node][jump];
  }
  return node;
}

/*
 * Znajduje pierwszy wierzchołek na ścieżce z wierzchołka do korzenia
 * w O(log d), gdzie d to długość ścieżki, spełniający dowolny warunek
 * monotoniczny niemalejący (jak wiadomo, true to 1, a false to 0) lub -1,
 * jeśli taki wierzchołek nie istnieje.
 */
template<class Predicate>
int worse_lifting_find_first(vector<vector<int>> const& lift,
                       int node, Predicate pred = Predicate())
{
  int const n = lift.size();

  if(pred(node)) {
    return node;
  }

  int max_jump = INT_MAX;
  while(!lift[node].empty() && !pred(lift[node][0])) {
    int jump = min(max_jump, (int) lift[node].size() - 1);
    while(pred(lift[node][jump])) {
      jump--;
      max_jump = jump;
    }
    node = lift[node][jump];
  }
  return lift[node].empty() ? -1 : lift[node][0];
}
