#include "math/discrete_log.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    Z<MOD> a, b, k;
    cin >> a >> b >> k;

    auto result = discrete_log(a, b, k);
    if(result) {
      cout << *result << endl;
      assert(k * a.pow(*result) == b);
    } else {
      cout << "nullopt" << endl;
    }
  }
}
