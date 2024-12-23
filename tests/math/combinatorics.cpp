#include "math/combinatorics.hpp"
#include "iostream.hpp"

int main() {
  using Z = Z<MOD>;
  ll skip;
  cin >> skip;
  SkipFac<Z> fac(skip);
  Subfac<Z> subfac;

  while(cin) {
    string op;
    cin >> op;

    if(op == "fac") {
      ll x;
      cin >> x;

      cout << fac(x) << endl;

    } else if(op == "inv_fac") {
      ll x;
      cin >> x;

      cout << fac.inv(x) << endl;

    } else if(op == "fac_decl") {
      auto encode = [&](vector<Z> const& nums) {
        string base64;
        for(auto num: nums | v::reverse | v::transform(&Z::operator ll)) {
          base64.push_back(';');
          while(num > 0) {
            base64.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[num & 0x3f]);
            num >>= 6;
          }
        }
        r::reverse(base64);
        for(auto i = 0; i < base64.size(); i += 10'000) {
          cout << "    \"" << string_view(base64).substr(i, 10'000) << "\"\n";
        }
      };

      cout << "static_assert(Z::mod == " << MOD << ");\n"
              "SkipFac<Z> fac(" << fac.skip << ");\n"
              "{\n"
              "  array<int, 128> map;\n"
              "  for(auto i: v::iota(0, 64)) {\n"
              "    map[\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\"[i]] = i;\n"
              "  }\n"
              "  auto decode = [&](string const& base64) {\n"
              "    vector<Z> result;\n"
              "    ull num = 0;\n"
              "    for(auto c: base64) {\n"
              "      if(c == ';') {\n"
              "        result.push_back(num);\n"
              "        num = 0;\n"
              "      } else {\n"
              "        num <<= 6;\n"
              "        num |= map[c];\n"
              "      }\n"
              "    }\n"
              "    return move(result);\n"
              "  };\n"
              "  fac.fac = decode(\n";
      encode(fac.fac);
      cout << "  );\n"
              "  fac.inv_fac = decode(\n";
      encode(fac.inv_fac);
      cout << "  );\n"
              "}" << endl;

    } else if(op == "choose") {
      int n, k;
      cin >> n >> k;

      cout << choose(n, k, fac) << endl;
      assert(choose<Z>(n, k) == choose(n, k, fac));

    } else if(op == "any_in_uniq") {
      int n, k;
      cin >> n >> k;

      cout << any_in_uniq(n, k, fac) << endl;

    } else if(op == "uniq_in_uniq") {
      int n, k;
      cin >> n >> k;

      cout << uniq_in_uniq(n, k, fac) << endl;

    } else if(op == "catalan") {
      int n;
      cin >> n;

      cout << catalan(n, fac) << endl;

    } else if(op == "subfac") {
      int n;
      cin >> n;

      cout << subfac(n) << endl;

    } else if(op == "burnside") {
      int n, k;
      cin >> n >> k;

      cout << burnside<Z>(n, k) << endl;
    }
  }
}
