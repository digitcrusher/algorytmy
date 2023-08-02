#include "string/manacher.hpp"
#include <iostream>

int main() {
  while(true) {
    string s;
    cin >> s;
    if(!cin) break;

    auto [odd, even] = manacher(s);
    for(auto i: odd) {
      cout << 2 * i + 1 << " ";
    }
    cout << endl;
    for(auto i: even) {
      cout << " " << 2 * i;
    }
    cout << endl;
  }
}
