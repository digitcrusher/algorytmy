#include "string/min_rot.hpp"
#include "iostream.hpp"
#include <algorithm>

int main() {
  while(cin) {
    string s;
    cin >> s;

    auto result = min_rot(s);
    rotate(s.begin(), s.begin() + result, s.end());
    cout << result + 1 << endl;
    cout << s << endl;
  }
}
