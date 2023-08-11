#include "other/lis.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<ll> nums(n);
    cin >> nums;

    auto result = lis(nums);
    for(auto i: result) {
      cout << nums[i] << " ";
    }
    cout << endl;
    assert(result == lis_segtree(nums));
  }
}
