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
    cout << (lift | v::transform(λ(_ + 1))) << endl;

    auto worse_lift = worse_binary_lift(parent);
    cout << "worse:" << endl;
    for(auto &i: worse_lift) {
      cout << (i | v::transform(λ(_ + 1))) << endl;
    }

    worse_lift = worse_binary_lift_light(parent);
    cout << "worse light:" << endl;
    for(auto &i: worse_lift) {
      cout << (i | v::transform(λ(_ + 1))) << endl;
    }
  }
}
