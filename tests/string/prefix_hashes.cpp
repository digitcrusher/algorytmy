#include "string/prefix_hashes.hpp"
#include "iostream.hpp"

int main() {
  string str;
  cin >> str;

  struct AlphaToNum {
    int operator()(char c) {
      return c - 'a';
    }
  };
  PrefixHashes<Z<MOD>, 'z' - 'a' + 1, AlphaToNum> prefix_hashes(str);

  while(cin) {
    int a, b;
    cin >> a >> b;
    a--, b--;

    cout << prefix_hashes.get(a, b) << endl;
  }
}
