#include "graph/offline_dynamic_connectivity.hpp"
#include <iostream>

int main() {
  while(true) {
    int n, q;
    cin >> n >> q;
    if(!cin) break;
    vector<Query> queries(q);
    for(auto &[type, a, b]: queries) {
      string op;
      cin >> op >> a >> b;
      if(!cin) break;
      type = op == "add" ? Query::add : Query::remove;
      a--, b--;
    }
    if(!cin) break;

    auto results = offline_dynamic_connectivity(n, queries);
    for(auto i: results) {
      cout << i << " ";
    }
    cout << "\n";
  }
}
