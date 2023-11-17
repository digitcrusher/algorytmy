#include "graph/path.hpp"
#include "iostream.hpp"

int main() {
  vector<vector<int>> adj, rev_adj;

  while(cin) {
    string op;
    cin >> op;

    if(op == "dag") {
      int n, m;
      cin >> n >> m;
      adj.clear();
      adj.resize(n);
      rev_adj.clear();
      rev_adj.resize(n);
      for(auto i: v::iota(0, m)) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
      }

    } else if(op == "tree") {
      int n;
      cin >> n;
      adj.clear();
      adj.resize(n);
      for(auto i: v::iota(0, n - 1)) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
      }

    } else if(op == "count_paths_dag") {
      int src;
      cin >> src;
      src--;

      cout << count_paths_dag(rev_adj, src) << endl;

    } else if(op == "longest_path_dag") {
      int from, to;
      cin >> from >> to;
      from--, to--;

      auto result = longest_path_dag(adj, from, to);
      if(result) {
        cout << (*result | v::transform(λ(_ + 1))) << endl;
      } else {
        cout << "nullopt" << endl;
      }

    } else if(op == "max_dist_tree") {
      auto result = max_dist_tree(adj);
      cout << result.max_dist;
      cout << result.a + 1 << " " << result.b + 1 << endl;
    }
  }
}
