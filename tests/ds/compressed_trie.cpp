#include "ds/compressed_trie.hpp"
#include <iostream>

int main() {
  auto alpha_to_num = [](char c) -> int {
    return c - 'a';
  };
  auto num_to_alpha = [](int i) -> char {
    return i + 'a';
  };
  CompressedTrie<
    int, 'z' - 'a' + 1,
    decltype(alpha_to_num),
    decltype(num_to_alpha)
  > trie(alpha_to_num, num_to_alpha);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "keys") {
      for(string key: trie.keys()) {
        cout << key << endl;
      }
    } else {
      string key;
      cin >> key;
      if(!cin) break;

      if(op == "get") {
        cout << trie.get(key) << endl;
      } else if(op == "has") {
        cout << boolalpha << trie.has(key) << endl;
      } else if(op == "set") {
        int val;
        cin >> val;
        if(!cin) break;
        trie.set(key, val);
      } else if(op == "erase") {
        cout << boolalpha << trie.erase(key) << endl;
      }
    }
  }
}
