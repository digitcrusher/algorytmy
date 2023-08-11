#include "string/manacher.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string s;
    cin >> s;

    auto result = manacher(s);
    for(auto i: result.odd) {
      cout << 2 * i + 1 << " ";
    }
    cout << endl;
    for(auto i: result.even) {
      cout << " " << 2 * i;
    }
    cout << endl;
  }
}
