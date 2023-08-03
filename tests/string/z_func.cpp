#include "string/z_func.hpp"
#include <iostream>

int main() {
  while(true) {
    string s;
    cin >> s;
    if(!cin) break;

    auto result = z_func(s);
    for(auto i: result) {
      cout << i << " ";
    }
    cout << endl;
  }
}
