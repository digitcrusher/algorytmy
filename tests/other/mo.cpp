#include "other/mo.hpp"
#include "ds/sqrt_sums.hpp"
#include "iostream.hpp"
#include <unordered_map>

// Zapytania o medianę na przedziale w O((n + q) * sqrt(n)).

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

  auto sorted = nums;
  r::sort(sorted);
  int uniquec = r::unique(sorted).begin() - sorted.begin();
  unordered_map<ll, int> norm;
  for(auto i: v::iota(0, uniquec)) {
    norm[sorted[i]] = i;
  }

  vector<ll> results(q);

  SqrtSums<int, plus<int>, int, plus<int>> cnt(vector(uniquec, 0));
  auto add = [&](int idx) {
    cnt.modify(norm[nums[idx]], 1);
  };
  auto remove = [&](int idx) {
    cnt.modify(norm[nums[idx]], -1);
  };
  auto find = [&](int idx) {
    auto result = 0;
    while(idx >= cnt.sums[result / cnt.block_size]) {
      idx -= cnt.sums[result / cnt.block_size];
      result += cnt.block_size;
    }
    while(idx >= cnt.elems[result]) {
      idx -= cnt.elems[result];
      result++;
    }
    return sorted[result];
  };
  int l, r;
  auto init = [&](int left, int right) {
    l = left, r = right;
    cnt.elems.assign(cnt.elems.size(), 0);
    cnt.sums.assign(cnt.sums.size(), 0);
    for(auto i: v::iota(l, r + 1)) {
      cnt.modify(norm[nums[i]], 1);
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
    results[idx] = find((r - l) / 2) + find((r - l + 1) / 2);
  };
  mo(
    n, queries, init,
    expand_left, expand_right,
    shrink_left, shrink_right, answer
  );

  for(auto i: results) {
    cout << i / 2 << "." << i % 2 * 5 << endl;
  }
}
