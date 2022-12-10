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
    int l, r;
    cin >> l >> r;
    if(!cin) break;
    l--, r--;
    cout << prefix_hashes.get(l, r) << endl;
  }
}
