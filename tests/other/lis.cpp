#include "other/lis.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<ll> nums(n);
    cin >> nums;

    auto result = lis(nums);
    cout << (result | v::transform(λ(nums[_]))) << endl;
    assert(result == lis_segtree(nums));
  }
}
