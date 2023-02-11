#include "graph/binary_lift.hpp"
#include <iostream>

int main() {
  while(true) {
    int n;
    cin >> n;
    if(!cin) break;
    vector<int> parent(n);
    for(int &num: parent) {
      cin >> num;
      if(!cin) break;
      if(num != -1) {
        num--;
      }
    }
    if(!cin) break;

    auto result1 = binary_lift(parent);
    cout << "normal: ";
    for(int i: result1) {
      cout << i + 1 << " ";
    }
    cout << endl;

    auto result2 = worse_binary_lift(parent);
    cout << "worse:" << endl;
    for(int i = 0; i < n; i++) {
      for(int j: result2[i]) {
        cout << j + 1 << " ";
      }
      cout << endl;
    }

    result2 = worse_binary_lift_light(parent);
    cout << "worse light:" << endl;
    for(int i = 0; i < n; i++) {
      for(int j: result2[i]) {
        cout << j + 1 << " ";
      }
      cout << endl;
    }
  }
}
