#include "string/min_rot.hpp"
#include <algorithm>
#include <iostream>

int main() {
  while(true) {
    string s;
    cin >> s;
    if(!cin) break;

    auto result = min_rot(s);
    rotate(s.begin(), s.begin() + result, s.end());
    cout << result + 1 << endl;
    cout << s << endl;
  }
}
