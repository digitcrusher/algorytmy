#include "string/suffix_array.hpp"
#include <iostream>

int main() {
  while(true) {
    string s;
    cin >> s;
    if(!cin) break;

    struct AlphaToNum {
      int operator()(char c) {
        return c - 'a';
      }
    };
    auto result = suffix_array<26, AlphaToNum>(s);
    for(int i: result) {
      cout << i + 1 << " ";
    }
    cout << endl;
  }
}
