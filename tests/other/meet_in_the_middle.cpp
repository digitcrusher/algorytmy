#include "other/meet_in_the_middle.hpp"
#include <iostream>

int main() {
  while(true) {
    int n;
    ll target;
    cin >> n >> target;
    if(!cin) break;
    vector<ll> nums(n);
    for(auto &i: nums) {
      cin >> i;
      if(!cin) break;
    }
    if(!cin) break;

    cout << subset_sum(nums, target) << endl;
  }
}
