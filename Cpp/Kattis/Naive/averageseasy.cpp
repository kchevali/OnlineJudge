#include <bits/stdc++.h>
using namespace std;
typedef long long l;

const l N = 1000 + 10;
l x[N], y[N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l t;
  scanf("%lld", &t);
  for (l i = 0; i < t; i++) {
    l a, b;
    double totA = 0, totB = 0;
    scanf("%lld%lld", &a, &b);
    for (l j = 0; j < a; j++) {
      scanf("%lld", x + j);
      totA += x[j];
    }
    for (l j = 0; j < b; j++) {
      scanf("%lld", y + j);
      totB += y[j];
    }
    totA /= a;
    totB /= b;

    l ans = 0;
    for (l j = 0; j < a; j++)
      if (x[j] > totB && x[j] < totA) ans++;
    printf("%lld\n", ans);
  }
}
