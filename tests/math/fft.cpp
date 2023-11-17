#include "math/fft.hpp"
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

    } else if(op.substr(0, 3) == "mul") {
      int m;
      cin >> m;
      vector<cld> b(m);
      cin >> b;

      mul(a, b);
      if(op.substr(3) == "_real") {
        for(auto &i: a) {
          i = i.real();
        }
      } else if(op.substr(3) == "_int") {
        for(auto &i: a) {
          i = round(i.real());
        }
      }
    }

    cout << a << endl;
  }
}
