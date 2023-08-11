#include "ds/prefix_sums/1d.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> nums(n);
  cin >> nums;

  PrefixSums<ll, plus<ll>, minus<ll>> prefix_sums(nums);

  while(cin) {
    int a, b;
    cin >> a >> b;
    a--, b--;

    cout << prefix_sums.get(a, b) << endl;
  }
}
