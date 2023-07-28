#include "string/suffix_array.hpp"
#include <iostream>

int main() {
  while(true) {
    string s;
    cin >> s;
    if(!cin) break;

    auto result = suffix_array(s);
    for(auto i: result) {
      for(int j = i; j < s.size(); j++) {
        cout << s[j];
      }
      cout << " " << i + 1 << endl;
    }
    struct AlphaToNum {
      int operator()(char c) {
        return c - 'a';
      }
    };
    assert((result == suffix_array_hash<26, AlphaToNum>(s)));
  }
}
