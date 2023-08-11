#include "other/mo.hpp"
#include "iostream.hpp"
#include <unordered_map>

// Zapytania są o liczbę różnych elementów na przedziale.

int main() {
  int n;
  cin >> n;
  vector<ll> nums(n);
  cin >> nums;
  int q;
  cin >> q;
  vector<pair<int, int>> queries(q);
  for(auto &[a, b]: queries) {
    cin >> a >> b;
    a--, b--;
  }

  vector<int> results(q);

  unordered_map<ll, int> cnt;
  auto add = [&](int idx) {
    cnt[nums[idx]]++;
  };
  auto remove = [&](int idx) {
    cnt[nums[idx]]--;
    if(cnt[nums[idx]] == 0) {
      cnt.erase(nums[idx]);
    }
  };
  int l, r;
  auto init = [&](int left, int right) {
    l = left, r = right;
    cnt.clear();
    for(int i = l; i <= r; i++) {
      cnt[nums[i]]++;
    }
  };
  auto expand_left = [&]() {
    add(--l);
  };
  auto expand_right = [&]() {
    add(++r);
  };
  auto shrink_left = [&]() {
    remove(l++);
  };
  auto shrink_right = [&]() {
    remove(r--);
  };
  auto answer = [&](int idx) {
    results[idx] = cnt.size();
  };
  mo(
    n, queries, init,
    expand_left, expand_right,
    shrink_left, shrink_right, answer
  );

  cout << results << endl;
}
