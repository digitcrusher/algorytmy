#include "graph/shortest_path.hpp"
#include "graph/toposort.hpp"
#include <iostream>

int main() {
  int n, m;
  vector<vector<Edge>> adj;
  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "graph") {
      cin >> n >> m;
      if(!cin) break;
      adj.clear();
      adj.resize(n);
      for(int i = 0; i < m; i++) {
        int a, b, cost;
        cin >> a >> b >> cost;
        if(!cin) break;
        a--, b--;
        adj[a].push_back({b, cost});
      }
      if(!cin) break;

    } else if(!adj.empty()) {
      if(op.substr(0, 5) == "sssp_") {
        int src;
        cin >> src;
        if(!cin) break;
        src--;

        SingleSource result;
        if(op == "sssp_dag_dfs") {
          vector<vector<Edge>> rev_adj(adj.size());
          for(int i = 0; i < n; i++) {
            for(auto edge: adj[i]) {
              rev_adj[edge.neighbor].push_back({i, edge.cost});
            }
          }
          result = sssp_dag_dfs(rev_adj, src);
        } else if(op == "sssp_dag_toposort") {
          vector<vector<int>> costless_adj(n);
          for(int i = 0; i < n; i++) {
            for(auto edge: adj[i]) {
              costless_adj[i].push_back(edge.neighbor);
            }
          }
          result = sssp_dag_toposort(adj, src, toposort_dfs(costless_adj));
        } else if(op == "sssp_dijkstra") {
          result = sssp_dijkstra(adj, src);
        } else if(op == "sssp_dial") {
          result = sssp_dial(adj, src);
        } else if(op == "sssp_bellman_ford") {
          result = sssp_bellman_ford(adj, src);
        } else if(op == "sssp_spfa") {
          result = sssp_spfa(adj, src);
        }

        for(int i: result.dist) {
          if(i == INT_MAX) {
            cout << "∞ ";
          } else {
            cout << i << " ";
          }
        }
        cout << endl;
        for(int i: result.prev) {
          cout << (i == -1 ? -1 : i + 1) << " ";
        }
        cout << endl;

      } else if(op == "apsp_floyd_warshall") {
        auto result = apsp_floyd_warshall(adj);

        for(auto &row: result.dist) {
          for(int cell: row) {
            if(cell == INT_MAX) {
              cout << "+∞ ";
            } else if(cell == INT_MIN) {
              cout << "-∞ ";
            } else {
              cout << cell << " ";
            }
          }
          cout << endl;
        }
        for(auto &row: result.next) {
          for(int cell: row) {
            cout << (cell == -1 ? -1 : cell + 1) << " ";
          }
          cout << endl;
        }
      }
    }
  }
}
