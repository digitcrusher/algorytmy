#include "string/prefix_function.hpp"
#include <iostream>

int main() {
  while(true) {
    string s;
    cin >> s;
    if(!cin) break;

    auto result = prefix_function(s);
    for(int i: result) {
      cout << i << " ";
    }
    cout << endl;
  }
}
