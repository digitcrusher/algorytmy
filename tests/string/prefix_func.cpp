#include "string/prefix_func.hpp"
#include <iostream>

int main() {
  while(true) {
    string s;
    cin >> s;
    if(!cin) break;

    auto result = prefix_func(s);
    for(int i: result) {
      cout << i << " ";
    }
    cout << endl;
  }
}
