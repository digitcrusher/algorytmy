#include "string/prefix_hashes.hpp"
#include "iostream.hpp"

int main() {
  string str;
  ll mod;
  cin >> str >> mod;

  struct AlphaToNum {
    int operator()(char c) {
      return c - 'a';
    }
  };
  PrefixHashes<'z' - 'a' + 1, AlphaToNum> prefix_hashes(str, mod);

  while(cin) {
    int a, b;
    cin >> a >> b;
    a--, b--;

    cout << prefix_hashes.get(a, b) << endl;
  }
}
