#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
typedef long long l;
#define gc getchar_unlocked

void read(l &x) {
  l c = gc();
  x = 0;
  for (; ((c < 48 || c > 57)); c = gc())
    ;
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l t, n, i, len, j, x;

  read(t);
  fpp(i, 0, t) {
    read(len);
    read(n);
    l maxDist = 0, minDist = 0;
    fpp(j, 0, n) {
      read(x);
      maxDist = max(max(x, len - x), maxDist);
      minDist = max(min(x, len - x), minDist);
    }
    cout << minDist << " " << maxDist << "\n";
  }
}