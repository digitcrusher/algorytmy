#include "ds/sqrt_sums.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> nums(n);
  cin >> nums;

  SqrtSums<ll, plus<>, ll, plus<>> sqrt_sums(nums);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int a, b;
      cin >> a >> b;
      a--, b--;

      cout << sqrt_sums.get(a, b) << endl;

    } else if(op == "modify") {
      int idx;
      ll change;
      cin >> idx >> change;
      idx--;

      sqrt_sums.modify(idx, change);
    }
  }
}
