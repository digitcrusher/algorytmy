/*
 * Graf funkcyjny - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <algorithm>
#include <functional>
#include <optional>
#include <vector>

/*
 * Struktura na grafie funkcyjnym pozwalająca na operacje wielokrotnego
 * aplikowania funkcji (apply) w O(log n), obliczenia czasu do zacyklenia
 * (time_to_cycle) oraz obliczenia odległości do wierzchołka (dist) w O(1).
 */
struct FuncGraph {
  int n;
  vector<int> next;

  vector<vector<int>> cycles;
  struct Subtree {
    int cycle, idx;
  };
  vector<Subtree> subtree;

  vector<int> depth, jump;

  vector<vector<int>> prev;
  vector<int> entry, exit;

  FuncGraph(vector<int> const& next):
    n(next.size()), next(next), subtree(n),
    depth(n), jump(n),
    prev(n), entry(n), exit(n)
  {
    vector<bool> is_vis(n, false);
    for(int root = 0; root < n; root++) {
      if(is_vis[root]) continue;

      vector<int> path;
      int node = root;
      while(!is_vis[node]) {
        is_vis[node] = true;
        path.push_back(node);
        node = next[node];
      }

      auto cycle_begin = find(path.begin(), path.end(), node);
      if(cycle_begin != path.end()) {
        cycles.emplace_back(cycle_begin, path.end());
        path.erase(cycle_begin, path.end());
        auto &cycle = cycles.back();
        for(int i = 0; i < cycle.size(); i++) {
          auto node = cycle[i];
          subtree[node] = {cycles.size() - 1, i};

          depth[node] = 0;
          jump[node] = node;
        }
      }

      for(int i = path.size() - 1; i >= 0; i--) {
        auto node = path[i];
        subtree[node] = subtree[next[node]];

        depth[node] = depth[next[node]] + 1;
        auto p = next[node];
        if(depth[p] - depth[jump[p]] == depth[jump[p]] - depth[jump[jump[p]]]) {
          jump[node] = jump[jump[p]];
        } else {
          jump[node] = p;
        }

        prev[next[node]].push_back(node);
      }
    }

    int time = 0;
    function<void(int)> dfs = [&](int node) {
      entry[node] = time++;
      for(auto child: prev[node]) {
        dfs(child);
      }
      exit[node] = time++;
    };
    for(int root = 0; root < n; root++) {
      if(depth[root] != 0) continue;
      dfs(root);
    }
  }

  int apply(int node, ll times) {
    while(times > 0 && depth[node] > 0) {
      if(depth[node] - depth[jump[node]]) {
        times -= depth[node] - depth[jump[node]];
        node = jump[node];
      } else {
        times--;
        node = next[node];
      }
    }

    if(times > 0) {
      auto &cycle = cycles[subtree[node].cycle];
      node = cycle[(subtree[node].idx + times) % cycle.size()];
    }

    return node;
  }

  int time_to_cycle(int node) {
    return depth[node] + cycles[subtree[node].cycle].size();
  }

  optional<int> dist(int from, int to) {
    if(entry[to] <= entry[from] && exit[from] <= exit[to]) {
      return depth[from] - depth[to];
    } else if(subtree[from].cycle == subtree[to].cycle && depth[to] == 0) {
      auto on_cycle = subtree[to].idx - subtree[from].idx;
      if(on_cycle < 0) {
        on_cycle += cycles[subtree[to].cycle].size();
      }
      return depth[from] + on_cycle;
    } else {
      return nullopt;
    }
  }
};
