#include "ds/sparse_table.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> nums(n);
  cin >> nums;

  auto sum = λ2(min(_1, _2));
  SparseTable<ll, decltype(sum)> rmq(nums, sum);

  while(cin) {
    int a, b;
    cin >> a >> b;
    a--, b--;

    cout << rmq.get(a, b) << endl;
  }
}
