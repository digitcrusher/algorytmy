#include "graph/func_graph.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<int> next(n);
  for(auto &i: next) {
    cin >> i;
    i--;
  }

  FuncGraph graph(next);

  while(cin) {
    string op;
    cin >> op;

    if(op == "apply") {
      int node;
      ll times;
      cin >> node >> times;
      node--;

      cout << graph.apply(node, times) + 1 << endl;

    } else if(op == "time_to_cycle") {
      int node;
      cin >> node;
      node--;

      cout << graph.time_to_cycle(node) << endl;

    } else if(op == "dist") {
      int from, to;
      cin >> from >> to;
      from--, to--;

      auto result = graph.dist(from, to);
      if(result) {
        cout << *result << endl;
      } else {
        cout << "nullopt" << endl;
      }
    }
  }
}
