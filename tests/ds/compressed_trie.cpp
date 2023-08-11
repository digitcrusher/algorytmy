#include "ds/compressed_trie.hpp"
#include "iostream.hpp"

int main() {
  struct AlphaToNum {
    int operator()(char c) {
      return c - 'a';
    }
  };
  struct NumToAlpha {
    char operator()(int i) {
      return i + 'a';
    }
  };
  CompressedTrie<ll, 'z' - 'a' + 1, AlphaToNum, NumToAlpha> trie;

  while(cin) {
    string op;
    cin >> op;

    if(op == "keys") {
      cout << trie.keys();

    } else if(op == "get") {
      string key;
      cin >> key;

      cout << trie.get(key) << endl;

    } else if(op == "has") {
      string key;
      cin >> key;

      cout << boolalpha << trie.has(key) << endl;

    } else if(op == "set") {
      string key;
      ll val;
      cin >> key >> val;

      trie.set(key, val);

    } else if(op == "erase") {
      string key;
      cin >> key;

      cout << boolalpha << trie.erase(key) << endl;
    }
  }
}
