#include "graph/two_color.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    auto result = two_color(adj);
    if(result) {
      cout << *result << endl;
    } else {
      cout << "nullopt" << endl;
    }
  }
}
