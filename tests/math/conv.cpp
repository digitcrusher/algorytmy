#include "math/conv.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string op;
    int n;
    cin >> op >> n;
    vector<cld> a(n);
    cin >> a;

    if(op == "dft") {
      fft(a);

    } else if(op == "idft") {
      fft(a, true);

    } else if(op.starts_with("conv")) {
      int m;
      cin >> m;
      vector<cld> b(m);
      cin >> b;

      conv(a, b);
      if(op.ends_with("_real")) {
        for(auto &i: a) {
          i = i.real();
        }
      } else if(op.ends_with("_int")) {
        for(auto &i: a) {
          i = round(i.real());
        }
      }

    } else if(op == "wht3") {
      fwht3(a);

    } else if(op == "iwht3") {
      fwht3(a, true);

    } else if(op.starts_with("xor3_conv")) {
      int m;
      cin >> m;
      vector<cld> b(m);
      cin >> b;

      xor3_conv(a, b);
      if(op.ends_with("_real")) {
        for(auto &i: a) {
          i = i.real();
        }
      } else if(op.ends_with("_int")) {
        for(auto &i: a) {
          i = round(i.real());
        }
      }
    }

    cout << a << endl;
  }
}
