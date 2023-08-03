#include "string/aho_corasick.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;
  vector<string> keys(n);
  for(auto &i: keys) {
    cin >> i;
  }

  struct AlphaToNum {
    int operator()(char c) {
      return c - 'a';
    }
  };
  AhoCorasick<26, AlphaToNum> dict(keys);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "find_in") {
      string s;
      cin >> s;
      if(!cin) break;

      auto result = dict.find_in(s);
      for(auto i: result) {
        cout << (i == -1 ? -1 : i + 1) << " ";
      }
      cout << endl;

    } else if(op == "count_in") {
      string s;
      cin >> s;
      if(!cin) break;

      auto result = dict.count_in(s);
      for(auto i: result) {
        cout << i << " ";
      }
      cout << endl;
    }
  }
}
