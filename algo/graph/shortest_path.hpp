/*
 * Najkrótsze ścieżki - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include <climits>
#include <functional>
#include <queue>
#include <stdexcept>
#include <vector>

struct Edge {
  int neighbor;
  int cost;
};

struct SingleSource {
  vector<int> dist, prev;
};

/*
 * Znajduje najkrótszą ścieżkę z wierzchołka src do każdego innego w
 * skierowanym grafie acyklicznym w O(V + E). Na wejściu przyjmuje graf
 * z odwróconymi krawędziami.
 */
SingleSource sssp_dag_dfs(vector<vector<Edge>> const& rev_adj, int src) {
  int const n = rev_adj.size();

  vector<int> dist(n, INT_MAX), prev(n, -1);

  vector<bool> is_vis(n, false);
  dist[src] = 0;
  is_vis[src] = true;
  function<void(int)> dfs = [&](int node) {
    if(is_vis[node]) return;
    is_vis[node] = true;

    for(auto [parent, cost]: rev_adj[node]) {
      dfs(parent);
      if(dist[parent] == INT_MAX) continue;
      if(dist[node] > dist[parent] + cost) {
        dist[node] = dist[parent] + cost;
        prev[node] = parent;
      }
    }
  };
  for(int root = 0; root < n; root++) {
    dfs(root);
  }

  return {dist, prev};
}

/*
 * Znajduje najkrótszą ścieżkę z wierzchołka src do każdego innego w
 * skierowanym grafie acyklicznym z użyciem sortowania topologicznego
 * w O(V + E).
 */
SingleSource sssp_dag_toposort(vector<vector<Edge>> const& adj, int src,
                               vector<int> const& toposort)
{
  int const n = adj.size();

  vector<int> dist(n, INT_MAX), prev(n, -1);

  dist[src] = 0;
  for(int node: toposort) {
    if(dist[node] == INT_MAX) continue;
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
SingleSource sssp_dijkstra(vector<vector<Edge>> const& adj, int src) {
  int const n = adj.size();

  vector<int> dist(n, INT_MAX), prev(n, -1);

  using QueueElem = pair<int, int>;
  priority_queue<QueueElem, vector<QueueElem>, greater<QueueElem>> q;
  dist[src] = 0;
  q.push({0, src});
  while(!q.empty()) {
    int dist_in_q = q.top().first;
    int node = q.top().second;
    q.pop();

    if(dist_in_q != dist[node]) continue;

    for(auto [neighbor, cost]: adj[node]) {
      if(dist[neighbor] > dist[node] + cost) {
        dist[neighbor] = dist[node] + cost;
        prev[neighbor] = node;
        q.push({dist[neighbor], neighbor});
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
SingleSource sssp_dial(vector<vector<Edge>> const& adj, int src) {
  int const n = adj.size();

  vector<int> dist(n, INT_MAX), prev(n, -1);

  deque<vector<int>> layers(1);
  dist[src] = 0;
  layers[0].push_back(src);
  for(int layer_dist = 0; !layers.empty(); layer_dist++) {
    for(int node: layers.front()) {
      if(layer_dist != dist[node]) continue;

      for(auto [neighbor, cost]: adj[node]) {
        assert(cost >= 0);
        if(dist[neighbor] > dist[node] + cost) {
          dist[neighbor] = dist[node] + cost;
          prev[neighbor] = node;
          int i = dist[neighbor] - layer_dist;
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
SingleSource sssp_bellman_ford(vector<vector<Edge>> const& adj, int src) {
  int const n = adj.size();

  vector<int> dist(n, INT_MAX), prev(n, -1);

  dist[src] = 0;
  bool was_relaxed = true;
  for(int i = 0; i < n - 1 && was_relaxed; i++) {
    was_relaxed = false;
    for(int node = 0; node < n; node++) {
      if(dist[node] == INT_MAX) continue;
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
    for(int node = 0; node < n; node++) {
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
SingleSource sssp_spfa(vector<vector<Edge>> const& adj, int src) {
  int const n = adj.size();

  vector<int> dist(n, INT_MAX), prev(n, -1);

  queue<int> q;
  vector<bool> is_in_q(n, false);
  dist[src] = 0;
  q.push(0);
  is_in_q[src] = true;
  while(!q.empty()) {
    int node = q.front();
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
  vector<vector<int>> dist; // dist[from][to]
  vector<vector<int>> next; // next[from][to]
};

/*
 * Algorytm Floyda-Warshalla -
 *   Znajduje najkrótszą ścieżkę dla każdej pary
 *   wierzchołków w grafie skierowanym w O(V^3).
 */
AllPairs apsp_floyd_warshall(vector<vector<Edge>> const& adj) {
  int const n = adj.size();

  vector<vector<int>> dist(n, vector<int>(n, INT_MAX)), next(n, vector<int>(n, -1));

  for(int node = 0; node < n; node++) {
    dist[node][node] = 0;
    for(auto [neighbor, cost]: adj[node]) {
      dist[node][neighbor] = cost;
      next[node][neighbor] = neighbor;
    }
  }
  for(int c = 0; c < n; c++) {
    for(int a = 0; a < n; a++) {
      for(int b = 0; b < n; b++) {
        if(dist[a][c] == INT_MAX || dist[c][b] == INT_MAX) continue;
        if(dist[c][c] < 0) {
          dist[a][b] = INT_MIN;
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
