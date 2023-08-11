#include "string/suffix_array.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string s;
    cin >> s;

    auto result = suffix_array(s);
    for(auto i: result) {
      for(int j = i; j < s.size(); j++) {
        cout << s[j];
      }
      cout << " " << i + 1 << endl;
    }
    cout << lcp(s, result) << endl;

    struct AlphaToNum {
      int operator()(char c) {
        return c - 'a';
      }
    };
    assert((result == suffix_array_hash<'z' - 'a' + 1, AlphaToNum>(s)));
  }
}
