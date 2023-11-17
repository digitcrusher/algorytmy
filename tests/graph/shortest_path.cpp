#include "graph/shortest_path.hpp"
#include "graph/toposort.hpp"
#include "iostream.hpp"

int main() {
  int n, m;
  vector<vector<pair<int, ll>>> adj;

  while(cin) {
    string op;
    cin >> op;

    if(op == "graph") {
      cin >> n >> m;
      adj.clear();
      adj.resize(n);
      for(auto i: v::iota(0, m)) {
        int a, b;
        ll cost;
        cin >> a >> b >> cost;
        a--, b--;
        adj[a].emplace_back(b, cost);
      }

    } else if(op.substr(0, 5) == "sssp_") {
      int src;
      cin >> src;
      src--;

      SingleSource result;

      if(op == "sssp_dag_dfs") {
        vector<vector<pair<int, ll>>> rev_adj(adj.size());
        for(auto a: v::iota(0, n)) {
          for(auto [b, cost]: adj[a]) {
            rev_adj[b].emplace_back(a, cost);
          }
        }
        result = sssp_dag_dfs(rev_adj, src);

      } else if(op == "sssp_dag_toposort") {
        vector<vector<int>> costless_adj(n);
        for(auto a: v::iota(0, n)) {
          for(auto [b, _]: adj[a]) {
            costless_adj[a].push_back(b);
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

      for(auto i: result.dist) {
        if(i == LLONG_MAX) {
          cout << "∞ ";
        } else {
          cout << i << " ";
        }
      }
      cout << endl;
      cout << (result.prev | v::transform(λ(_ == -1 ? -1 : _ + 1))) << endl;

    } else if(op == "apsp_floyd_warshall") {
      auto result = apsp_floyd_warshall(adj);

      for(auto &row: result.dist) {
        for(auto cell: row) {
          if(cell == LLONG_MAX) {
            cout << "+∞ ";
          } else if(cell == LLONG_MIN) {
            cout << "-∞ ";
          } else {
            cout << cell << " ";
          }
        }
        cout << endl;
      }
      for(auto &i: result.next) {
        cout << (i | v::transform(λ(_ == -1 ? -1 : _ + 1))) << endl;
      }
    }
  }
}
