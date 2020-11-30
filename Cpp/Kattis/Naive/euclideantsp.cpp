#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

#define db(args...)                           \
  {                                           \
    string _s = #args;                        \
    replace(_s.begin(), _s.end(), ' ', '\0'); \
    replace(_s.begin(), _s.end(), ',', ' ');  \
    stringstream _ss(_s);                     \
    istream_iterator<string> _it(_ss);        \
    err(_it, args);                           \
    cerr << "\n";                             \
  }
void err(istream_iterator<string> it) {}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " = " << a << "   ";
  err(++it, args...);
}

l n;
double p, s, v;

inline double f(double c) { return (s * (1 + 1 / c) / v) + (n * pow(log2(n), c * sqrt(2)) / (p * 1e9)); }
inline l sign(double x) { return x < 0 ? -1 : 1; }
// inline double g(double c) { return; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  scanf("%lld%lf%lf%lf", &n, &p, &s, &v);

  double a = 0.1, b = 500, EST = 1e-7;
  while (true) {
    double c = (2 * a + b) / 3, d = (a + 2 * b) / 3;
    // db(a, b, f(c));
    if (fabs(f(c)) < EST || fabs(a - b) < EST) {
      printf("%lf %lf", f(c), c);
      break;
    } else if (f(c) > f(d)) {
      a = c;
    } else {
      b = d;
    }
  }
}
