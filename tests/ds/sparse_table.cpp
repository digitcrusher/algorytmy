#include "ds/sparse_table.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> nums(n);
  cin >> nums;

  auto sum = (ll const&(*)(ll const&, ll const&)) min;
  SparseTable<ll, decltype(sum)> rmq(nums, sum);

  while(cin) {
    int a, b;
    cin >> a >> b;
    a--, b--;

    cout << rmq.get(a, b) << endl;
  }
}
