#include "string/aho_corasick.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<string> keys(n);
  cin >> keys;

  struct AlphaToNum {
    int operator()(char c) {
      return c - 'a';
    }
  };
  AhoCorasick<'z' - 'a' + 1, AlphaToNum> dict(keys);

  while(cin) {
    string op;
    cin >> op;

    if(op == "find_in") {
      string s;
      cin >> s;

      auto result = dict.find_in(s);
      for(auto i: result) {
        cout << (i == -1 ? -1 : i + 1) << " ";
      }
      cout << endl;

    } else if(op == "count_in") {
      string s;
      cin >> s;

      cout << dict.count_in(s) << endl;
    }
  }
}
