#include "math/primitive_root.hpp"
#include <iostream>

int main() {
  while(true) {
    ll mod;
    cin >> mod;
    if(!cin) break;

    auto result = primitive_root(mod);
    if(result == nullopt) {
      cout << "nullopt" << endl;
    } else {
      cout << *result << endl;
    }
  }
}
