#include "string/manacher.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string s;
    cin >> s;

    auto result = manacher(s);
    cout << (result.odd | v::transform(λ(2 * _ + 1))) << endl;
    cout << (result.even | v::transform(λ(2 * _))) << endl;
  }
}
