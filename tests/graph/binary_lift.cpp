#include "graph/binary_lift.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<int> parent(n);
    for(auto &i: parent) {
      cin >> i;
      if(i != -1) {
        i--;
      }
    }

    auto lift = binary_lift(parent);
    cout << "normal:" << endl;
    for(auto i: lift) {
      cout << i + 1 << " ";
    }
    cout << endl;

    auto worse_lift = worse_binary_lift(parent);
    cout << "worse:" << endl;
    for(auto &a: worse_lift) {
      for(auto b: a) {
        cout << b + 1 << " ";
      }
      cout << endl;
    }

    worse_lift = worse_binary_lift_light(parent);
    cout << "worse light:" << endl;
    for(auto &a: worse_lift) {
      for(auto b: a) {
        cout << b + 1 << " ";
      }
      cout << endl;
    }
  }
}
