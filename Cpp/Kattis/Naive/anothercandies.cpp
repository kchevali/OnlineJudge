#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
typedef long long l;
#define gc getchar_unlocked

void read(l &x) {
  l c = gc();
  x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc())
    ;
  if (c == '-') {
    neg = 1;
    c = gc();
  }
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
  if (neg) x = -x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l t, n, i, j;

  read(t);
  fpp(i, 0, t) {
    read(n);
    l sum = 0, x;
    fpp(j, 0, n) {
      read(x);
      sum = (sum + (x % n)) % n;
    }
    cout << (sum == 0 ? "YES" : "NO") << "\n";
  }
}
