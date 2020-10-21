// closed form
#include <bits/stdc++.h>
using namespace std;
typedef long long l;
#define dc(x) cout << fixed << setprecision(x) <<

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n;
  cin >> n;
  for (l i = 0; i < n; i++) {
    double w, a, b, r;
    cin >> w >> a >> b >> r;
    a -= r;
    b -= r;
    double mn = sqrt(w * w + (a - b) * (a - b));

    if (a == 0 || b == 0) {
      dc(8) mn << " " << mn << "\n";
      continue;
    }
    double x = (a * w) / (a + b);
    double p = sqrt(a * a + x * x);
    double q = sqrt(b * b + (w - x) * (w - x));
    dc(8) mn << " " << (p + q) << "\n";
  }
}
