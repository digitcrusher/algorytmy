#include "ds/sparse_table.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for(auto &num: nums) {
    cin >> num;
  }

  auto min = [](int a, int b) {
    return ::min(a, b);
  };
  SparseTable<int, decltype(min)> rmq(nums, min);

  while(true) {
    int a, b;
    cin >> a >> b;
    if(!cin) break;
    a--, b--;
    cout << rmq.get(a, b) << endl;
  }
}
