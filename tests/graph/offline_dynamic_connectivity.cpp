#include "graph/offline_dynamic_connectivity.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, q;
    cin >> n >> q;
    vector<Query> queries(q);
    for(auto &[type, a, b]: queries) {
      string op;
      cin >> op >> a >> b;
      a--, b--;
      if(op == "add") {
        type = Query::add;
      } else if(op == "remove") {
        type = Query::remove;
      } else if(op == "are_connected") {
        type = Query::are_connected;
      } else {
        assert(false);
      }
    }

    cout << boolalpha << offline_dynamic_connectivity(n, queries) << endl;
  }
}
