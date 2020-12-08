#include <bits/stdc++.h>
using namespace std;
typedef long long l;

const l N = 15 + 2;
l xs[N], ys[N], rs[N], dp[1 << N], n;
bool isGood[N][N];

l solve(l mask) {
  if (dp[mask] != -1) return dp[mask];
  l area = 0;
  for (l i = 0, bit = 1; i < n; i++, bit <<= 1) {
    if ((mask & bit) != 0) {
      bool allGood = true;
      for (l j = 0, bat = 1; j < n; j++, bat <<= 1) {
        if ((mask & bat) == 0 && !isGood[i][j]) {
          allGood = false;
          break;
        }
      }
      if (allGood) area = max(area, rs[i] * rs[i] + (mask == bit ? 0 : solve(mask ^ bit)));
    }
  }
  return dp[mask] = area;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l t;
  scanf("%lld", &t);
  for (l i = 0; i < t; i++) {
    scanf("%lld", &n);
    memset(dp, -1, sizeof(l) * (1 << n));
    for (l j = 0; j < n; j++) {
      scanf("%lld%lld%lld", xs + j, ys + j, rs + j);
      for (l k = 0; k < j; k++) {
        l dx = xs[j] - xs[k], dy = ys[j] - ys[k], r = rs[j] + rs[k];
        isGood[j][k] = isGood[k][j] = (dx * dx + dy * dy) > r * r;
      }
    }
    printf("%lld\n", solve((1 << n) - 1));
  }
}
