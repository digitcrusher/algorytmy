#include "string/search.hpp"
#include <iostream>

int main() {
  while(true) {
    string a, b;
    cin >> a >> b;
    if(!cin) break;
    struct AlphaToNum {
      int operator()(char c) {
        return c - 'a';
      }
    };
    auto result = search_rabin_karp<26, AlphaToNum>(a, b);
    for(int i: result) {
     cout << i + 1 << " ";
    }
    cout << endl;
    assert(result == search_kmp(a, b));
  }
}
