#include "string/suffix_array.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string s;
    cin >> s;

    auto result = suffix_array(s);
    for(auto i: result) {
      cout << (s | v::drop(i)) << " " << i + 1 << endl;
    }
    cout << lcp(s, result) << endl;

    assert((result == suffix_array_hash<'z' - 'a' + 1>(s, λ(_ - 'a'))));
  }
}
