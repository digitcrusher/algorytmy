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
      if(op == "add") {
        type = Query::add;
      } else if(op == "remove") {
        type = Query::remove;
      } else if(op == "are_connected") {
        type = Query::are_connected;
      } else {
        assert(false);
      }
      a--, b--;
    }
    if(!cin) break;

    auto results = offline_dynamic_connectivity(n, queries);
    for(auto i: results) {
      cout << boolalpha << i << " ";
    }
    cout << "\n";
  }
}
