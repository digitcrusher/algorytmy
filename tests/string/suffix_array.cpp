#include "string/suffix_array.hpp"
#include <iostream>

int main() {
  while(true) {
    string s;
    cin >> s;
    if(!cin) break;

    auto suffix_array = ::suffix_array(s);
    for(auto i: suffix_array) {
      for(int j = i; j < s.size(); j++) {
        cout << s[j];
      }
      cout << " " << i + 1 << endl;
    }
    auto lcp = ::lcp(s, suffix_array);
    for(auto i: lcp) {
      cout << i << " ";
    }
    cout << endl;

    struct AlphaToNum {
      int operator()(char c) {
        return c - 'a';
      }
    };
    assert((suffix_array == suffix_array_hash<26, AlphaToNum>(s)));
  }
}
