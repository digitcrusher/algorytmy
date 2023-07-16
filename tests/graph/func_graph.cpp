#include "graph/func_graph.hpp"
#include <iostream>

int main() {
  optional<FuncGraph> graph;

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "graph") {
      int n;
      cin >> n;
      vector<int> next(n);
      for(auto &i: next) {
        cin >> i;
        i--;
      }
      graph.emplace(next);

    } else if(op == "apply") {
      int node;
      ll times;
      cin >> node >> times;
      if(!cin) break;
      node--;

      cout << graph->apply(node, times) + 1 << endl;

    } else if(op == "time_to_cycle") {
      int node;
      cin >> node;
      if(!cin) break;
      node--;

      cout << graph->time_to_cycle(node) << endl;

    } else if(op == "dist") {
      int from, to;
      cin >> from >> to;
      if(!cin) break;
      from--, to--;

      auto result = graph->dist(from, to);
      if(result == nullopt) {
        cout << "nullopt" << endl;
      } else {
        cout << *result << endl;
      }
    }
  }
}
