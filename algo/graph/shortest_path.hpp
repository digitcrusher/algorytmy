/*
 * Najkrótsze ścieżki - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <queue>

struct SingleSource {
  vector<ll> dist;
  vector<int> prev;
};

/*
 * Znajduje najkrótszą ścieżkę z wierzchołka src do każdego innego w
 * skierowanym grafie acyklicznym w O(V + E). Na wejściu przyjmuje graf
 * z odwróconymi krawędziami.
 */
SingleSource sssp_dag_dfs(vector<vector<pair<int, ll>>> const& rev_adj, int src) {
  int n = rev_adj.size();

  vector<ll> dist(n, LLONG_MAX);
  vector prev(n, -1);

  vector is_vis(n, false);
  dist[src] = 0;
  is_vis[src] = true;
  auto dfs = Y([&](auto &self, int node) -> void {
    if(is_vis[node]) return;
    is_vis[node] = true;

    for(auto [parent, cost]: rev_adj[node]) {
      self(parent);
      if(dist[parent] == LLONG_MAX) continue;
      if(dist[node] > dist[parent] + cost) {
        dist[node] = dist[parent] + cost;
        prev[node] = parent;
      }
    }
  });
  for(auto root: v::iota(0, n)) {
    dfs(root);
  }

  return {dist, prev};
}

/*
 * Znajduje najkrótszą ścieżkę z wierzchołka src do każdego innego w
 * skierowanym grafie acyklicznym z użyciem sortowania topologicznego
 * w O(V + E).
 */
SingleSource sssp_dag_toposort(vector<vector<pair<int, ll>>> const& adj, int src,
                               vector<int> const& toposort)
{
  int n = adj.size();

  vector<ll> dist(n, LLONG_MAX);
  vector prev(n, -1);

  dist[src] = 0;
  for(auto node: toposort | v::filter(λ(dist[_] != LLONG_MAX))) {
    for(auto [child, cost]: adj[node]) {
      if(dist[child] > dist[node] + cost) {
        dist[child] = dist[node] + cost;
        prev[child] = node;
      }
    }
  }

  return {dist, prev};
}

/*
 * Algorytm Dijkstry -
 *   Znajduje najkrótszą ścieżkę z wierzchołka src do każdego innego w grafie
 *   skierowanym z nieujemnymi wagami krawędzi w O(E log V). Wydaje mi się, że
 *   w grafie z ujemnymi wagami krawędzi działa w O(E * V log V), gdyż jest to
 *   po prostu SPFA z kolejką priorytetową, ale nieliczne źródła podają, że jest
 *   wtedy wykładniczy. W grafie z ujemnym cyklem nie zatrzyma się.
 */
SingleSource sssp_dijkstra(vector<vector<pair<int, ll>>> const& adj, int src) {
  int n = adj.size();

  vector<ll> dist(n, LLONG_MAX);
  vector prev(n, -1);

  using QueueElem = pair<ll, int>;
  priority_queue<QueueElem, vector<QueueElem>, greater<>> q;

  dist[src] = 0;
  q.emplace(0, src);

  while(!q.empty()) {
    auto [dist_in_q, node] = q.top();
    q.pop();

    if(dist_in_q != dist[node]) continue;

    for(auto [neighbor, cost]: adj[node]) {
      if(dist[neighbor] > dist[node] + cost) {
        dist[neighbor] = dist[node] + cost;
        prev[neighbor] = node;
        q.emplace(dist[neighbor], neighbor);
      }
    }
  }

  return {dist, prev};
}

/*
 * Algorytm Diala -
 *   Zmodyfikowany algorytm Dijkstry działający w O(E + V * C), gdzie C to
 *   największa waga krawędzi w grafie. Nie działa na grafach z ujemnymi
 *   wagami krawędzi.
 */
SingleSource sssp_dial(vector<vector<pair<int, ll>>> const& adj, int src) {
  int n = adj.size();

  vector<ll> dist(n, LLONG_MAX);
  vector prev(n, -1);

  deque<vector<int>> layers;
  dist[src] = 0;
  layers.push_back({src});

  for(auto layer_dist: v::iota(0) | v::take_while(λ(!layers.empty()))) {
    for(auto node: layers.front() | v::filter(λ(dist[_] == layer_dist))) {
      for(auto [neighbor, cost]: adj[node]) {
        assert(cost >= 0);
        if(dist[neighbor] > dist[node] + cost) {
          dist[neighbor] = dist[node] + cost;
          prev[neighbor] = node;
          auto i = dist[neighbor] - layer_dist;
          if(i >= layers.size()) {
            layers.resize(i + 1);
          }
          layers[i].push_back(neighbor);
        }
      }
    }
    layers.pop_front();
  }

  return {dist, prev};
}

/*
 * Algorytm Bellmana-Forda -
 *   Znajduje najkrótszą ścieżkę z wierzchołka src do
 *   każdego innego w grafie skierowanym w O(V * E).
 */
SingleSource sssp_bellman_ford(vector<vector<pair<int, ll>>> const& adj, int src) {
  int n = adj.size();

  vector<ll> dist(n, LLONG_MAX);
  vector prev(n, -1);

  dist[src] = 0;
  auto was_relaxed = true;
  for(auto i: v::iota(0, n - 1) | v::take_while(λ(was_relaxed))) {
    was_relaxed = false;
    for(auto node: v::iota(0, n) | v::filter(λ(dist[_] != LLONG_MAX))) {
      for(auto [neighbor, cost]: adj[node]) {
        if(dist[neighbor] > dist[node] + cost) {
          dist[neighbor] = dist[node] + cost;
          prev[neighbor] = node;
          was_relaxed = true;
        }
      }
    }
  }

  if(was_relaxed) {
    for(auto node: v::iota(0, n)) {
      for(auto [neighbor, cost]: adj[node]) {
        if(dist[neighbor] > dist[node] + cost) {
          throw std::runtime_error("Graf zawiera ujemny cykl.");
        }
      }
    }
  }

  return {dist, prev};
}

/*
 * Shortest Path Faster Algorithm (SPFA) -
 *   Znajduje najkrótszą ścieżkę z wierzchołka src do każdego innego w
 *   grafie skierowanym w O(V * E), ale zwykle jest szybszy od algorytmu
 *   Bellmana-Forda. W grafie z ujemnym cyklem nie zatrzyma się.
 */
SingleSource sssp_spfa(vector<vector<pair<int, ll>>> const& adj, int src) {
  int n = adj.size();

  vector<ll> dist(n, LLONG_MAX);
  vector prev(n, -1);

  queue<int> q;
  vector is_in_q(n, false);

  dist[src] = 0;
  q.push(0);
  is_in_q[src] = true;

  while(!q.empty()) {
    auto node = q.front();
    q.pop();
    is_in_q[node] = false;

    for(auto [neighbor, cost]: adj[node]) {
      if(dist[neighbor] > dist[node] + cost) {
        dist[neighbor] = dist[node] + cost;
        prev[neighbor] = node;
        if(!is_in_q[neighbor]) {
          q.push(neighbor);
          is_in_q[neighbor] = true;
        }
      }
    }
  }

  return {dist, prev};
}



struct AllPairs {
  vector<vector<ll>> dist;
  vector<vector<int>> next;
};

/*
 * Algorytm Floyda-Warshalla -
 *   Znajduje najkrótszą ścieżkę dla każdej pary
 *   wierzchołków w grafie skierowanym w O(V^3).
 */
AllPairs apsp_floyd_warshall(vector<vector<pair<int, ll>>> const& adj) {
  int n = adj.size();

  vector dist(n, vector<ll>(n, LLONG_MAX));
  vector next(n, vector(n, -1));

  for(auto node: v::iota(0, n)) {
    dist[node][node] = 0;
    for(auto [neighbor, cost]: adj[node]) {
      dist[node][neighbor] = cost;
      next[node][neighbor] = neighbor;
    }
  }
  for(auto c: v::iota(0, n)) {
    for(auto a: v::iota(0, n) | v::filter(λ(dist[_][c] != LLONG_MAX))) {
      for(auto b: v::iota(0, n) | v::filter(λ(dist[c][_] != LLONG_MAX))) {
        if(dist[c][c] < 0) {
          dist[a][b] = LLONG_MIN;
          next[a][b] = -1;
        } else if(dist[a][b] > dist[a][c] + dist[c][b]) {
          dist[a][b] = dist[a][c] + dist[c][b];
          next[a][b] = next[a][c];
        }
      }
    }
  }

  return {dist, next};
}
