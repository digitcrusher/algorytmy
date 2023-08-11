#include "other/meet_in_the_middle.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    ll target;
    cin >> n >> target;
    vector<ll> nums(n);
    cin >> nums;

    cout << subset_sum(nums, target) << endl;
  }
}
