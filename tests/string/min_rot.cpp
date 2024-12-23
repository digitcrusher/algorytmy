#include "string/min_rot.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string s;
    cin >> s;

    auto result = min_rot(s);
    r::rotate(s, s.begin() + result);
    cout << result + 1 << endl;
    cout << s << endl;
  }
}
