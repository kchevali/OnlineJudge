#include <bits/stdc++.h>
using namespace std;
typedef long long l;

const l N = 2000 + 10, C = 2000 + 10;  // max items, max wtacity
l dp[N][C];
l val[N], wt[N];  // input
bool included[N][C], ans[N];

// build dp table - run once per case
// Complexity: O(n*c)
l knapsack(l n, l c) {
  memset(dp, 0, sizeof(l) * n);
  memset(included, 0, sizeof(bool) * n);
  for (l i = 1; i <= n; i++) {
    dp[i][0] = included[i][0] = 0;
    for (l j = 1; j <= c; j++) {
      l a = val[i - 1] + dp[i - 1][j - wt[i - 1]];
      if (wt[i - 1] <= j && a > dp[i - 1][j]) {
        dp[i][j] = a;
        included[i][j] = true;
      } else {
        dp[i][j] = dp[i - 1][j];
        included[i][j] = false;
      }
    }
  }

  // get boolean indicies - included?
  l w = c, count = 0;
  for (l i = n - 1; i >= 0; i--)
    if ((ans[i] = included[i + 1][w])) {
      w -= wt[i];
      count++;
    }
  return count;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, c;
  while (scanf("%lld%lld", &c, &n) != EOF) {
    for (l i = 0; i < n; i++) {
      scanf("%lld", val + i);
      scanf("%lld", wt + i);
    }
    printf("%lld\n", knapsack(n, c));
    for (l i = 0; i < n; i++) {
      if (ans[i]) printf("%lld ", i);
    }
    printf("\n");
  }
}
