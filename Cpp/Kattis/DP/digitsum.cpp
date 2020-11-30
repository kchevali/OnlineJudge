#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

const l N = 16, M = 10, NM = N * M;
l dp[N][M];  // [number of zeros][starting digit]

l calc(l upper) {
  if (upper < 0) return 0;
  vl digits;
  l mult = 1;
  while (upper != 0) {
    digits.push_back(upper % 10);
    upper /= 10;
    mult *= 10;
  }
  l count = 0, prev = 0;
  for (l i = digits.size() - 1; i >= 0; i--) {
    mult /= 10;
    l digit = digits[i];
    count += dp[i][digit] + prev * digit * mult;
    prev += digit;
  }
  return count;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  memset(dp, 0, sizeof(l) * NM);
  for (l i = 0, mult = 1; i < N; i++, mult *= 10) {
    dp[i][1] = i == 0 ? 1 : dp[i - 1][M - 1] + dp[i - 1][1] + 9 * (mult / 10 - 1);
    for (l j = 2; j < M; j++) {
      dp[i][j] = dp[i][j - 1] + (mult * (j - 1)) + dp[i][1];
    }
  }
  l n;
  scanf("%lld", &n);
  for (l i = 0; i < n; i++) {
    l a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld\n", calc(b) - calc(a - 1));
  }
}
