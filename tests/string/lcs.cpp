#include "string/lcs.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string a, b;
    cin >> a >> b;

    cout << lcs_len(a, b) << endl;
    cout << lcs_dp(a, b);
    auto result = lcs_str(a, b);
    cout << result << endl;
    assert(result == lcs_str(a, b, lcs_dp(a, b)));
  }
}
