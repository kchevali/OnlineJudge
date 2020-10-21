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

  l n, notUpperBit = ~32;
  char s[10000], out[10000];
  read(n);

  while (n > 0) {
    l len = 0;
    char ch = gc(), uch = (ch & notUpperBit);
    while ((uch >= 'A' && uch <= 'Z') || ch == ' ') {
      if (ch != ' ') s[len++] = uch;
      uch = ((ch = gc()) & notUpperBit);
    }
    for (int i = 0, j = 0, k = 0; i < len; i++, j += n) {
      if (j >= len) j = ++k;
      out[j] = s[i];
    }
    l i;
    fpp(i, 0, len) cout << out[i];
    cout << "\n";
    read(n);
  }
}
