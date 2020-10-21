#include <bits/stdc++.h>
using namespace std;
#define fmm(i, a, b) for (i = b - 1; i >= a; i--)
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l a, b, c, i;
  cin >> a >> b >> c;
  l x = c, y = c, count = a / b + 1;

  fmm(i, 0, count) {
    if ((a - b * i) % c == 0) {
      x = i;
      y = (a - b * i) / c;
      break;
    }
  }
  if (x + y == 2 * c)
    cout << "impossible"
         << "\n";
  else
    cout << x << " " << y << "\n";
}
