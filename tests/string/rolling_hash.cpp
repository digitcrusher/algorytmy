#include "string/rolling_hash.hpp"
#include <iostream>

int main() {
  ll mod;
  cin >> mod;

  struct AlphaToNum {
    int operator()(char c) {
      return c - 'a';
    }
  };
  RollingHash<26, AlphaToNum> window(mod);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "front") {
      cout << window.front() << endl;
    } else if(op == "hash") {
      cout << window.hash << endl;
    } else if(op == "push") {
      char c;
      cin >> c;
      if(!cin) break;
      window.push(c);
    } else if(op == "pop") {
      window.pop();
    } else if(op == "clear") {
      window.clear();
    } else if(op == "empty") {
      cout << boolalpha << window.empty() << endl;
    } else if(op == "size") {
      cout << window.size() << endl;
    }
  }
}
