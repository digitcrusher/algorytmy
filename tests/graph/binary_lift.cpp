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

    auto result = binary_lift(parent);
    cout << "normal:" << endl;
    for(int i = 0; i < n; i++) {
      for(int j: result[i]) {
        cout << j + 1 << " ";
      }
      cout << endl;
    }

    result = light_binary_lift(parent);
    cout << "light:" << endl;
    for(int i = 0; i < n; i++) {
      for(int j: result[i]) {
        cout << j + 1 << " ";
      }
      cout << endl;
    }
  }
}
