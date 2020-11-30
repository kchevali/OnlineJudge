#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

l n, b;
const l N = 25, B = 15, inf = 1e15;

l xs[B], ys[B], allVis, startX, startY, dp[1 << B][N][N];

// complexity 2^10 * 20*20*25
l path(l vis, l x, l y) {
  if (dp[vis][x][y] != -1) return dp[vis][x][y];
  if (vis == allVis) return dp[vis][x][y] = abs(x - startX) + abs(y - startY);
  l cost = inf;
  for (l i = 0, bit = 1LL; i < b; i++, bit <<= 1) {
    if ((vis & bit) == 0) {
      cost = min(cost, abs(x - xs[i]) + abs(y - ys[i]) + path(vis | bit, xs[i], ys[i]));
    }
  }
  return dp[vis][x][y] = cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l t;
  scanf("%lld", &t);
  for (l i = 0; i < t; i++) {
    memset(dp, -1, sizeof(l) * (1 << B) * N * N);
    scanf("%lld%lld%lld%lld%lld", &n, &n, &startX, &startY, &b);
    for (l j = 0; j < b; j++) {
      scanf("%lld%lld", xs + j, ys + j);
    }
    allVis = (1 << b) - 1;
    printf("%lld\n", path(0, startX, startY));
  }
}
