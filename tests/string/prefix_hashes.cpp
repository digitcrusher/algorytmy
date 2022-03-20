#include "string/prefix_hashes.hpp"
#include <iostream>

int main() {
  string str;
  ll mod;
  cin >> str >> mod;

  struct AlphaToNum {
    int operator()(char c) {
      return c - 'a';
    }
  };
  PrefixHashes<26, AlphaToNum> prefix_hashes(str, mod);

  while(true) {
    int a, b;
    cin >> a >> b;
    if(!cin) break;
    a--, b--;
    cout << prefix_hashes.get(a, b) << endl;
  }
}
