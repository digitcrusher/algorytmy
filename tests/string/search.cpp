#include "string/search.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string a, b;
    cin >> a >> b;

    struct AlphaToNum {
      int operator()(char c) {
        return c - 'a';
      }
    };
    auto result = search_rabin_karp<'z' - 'a' + 1, AlphaToNum>(a, b);
    for(auto i: result) {
     cout << i + 1 << " ";
    }
    cout << endl;
    assert(result == search_kmp(a, b));
  }
}
