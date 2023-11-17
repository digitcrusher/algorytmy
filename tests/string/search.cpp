#include "string/search.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string a, b;
    cin >> a >> b;

    auto result = search_rabin_karp<'z' - 'a' + 1>(a, b, λ(_ - 'a'));
    cout << (result | v::transform(λ(_ + 1))) << endl;
    assert(result == search_kmp(a, b));
  }
}
