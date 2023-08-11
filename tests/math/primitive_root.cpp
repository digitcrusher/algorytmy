#include "math/primitive_root.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    ll mod;
    cin >> mod;

    auto result = primitive_root(mod);
    if(result) {
      cout << *result << endl;
    } else {
      cout << "nullopt" << endl;
    }
  }
}
