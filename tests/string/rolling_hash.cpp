#include "string/rolling_hash.hpp"
#include "iostream.hpp"

int main() {
  ll mod;
  cin >> mod;

  struct AlphaToNum {
    int operator()(char c) {
      return c - 'a';
    }
  };
  RollingHash<'z' - 'a' + 1, AlphaToNum> window(mod);

  while(cin) {
    string op;
    cin >> op;

    if(op == "front") {
      cout << window.front() << endl;

    } else if(op == "hash") {
      cout << window.hash << endl;

    } else if(op == "push") {
      char c;
      cin >> c;

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
