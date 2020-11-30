#include <bits/stdc++.h>
using namespace std;
typedef long long l;

l a, b, s;
const l N = 15, M = 136, NM = N * M;
l dp[N][M];

// input: upperbound + target sum
l upper(l a, l s) {
  if (a == 0) return (s == 0);

  vector<l> digit;
  while (a > 0) {
    digit.push_back(a % 10);
    a /= 10;
  }

  l count = 0, sum = 0;
  for (l i = digit.size() - 1; i >= 0; --i) {
    for (l d = 0; d < digit[i] && d <= s - sum; ++d) {
      count += dp[i][s - sum - d];
    }
    sum += digit[i];
  }
  return count + (sum == s ? 1 : 0);
}

// input lowerbound + target sum
l first(l a, l s) {
  l b = 1e15, t = upper(a, s) + 1;
  while (a < b) {
    l m = a + (b - a) / 2;
    if (upper(m, s) >= t)
      b = m;
    else
      a = m + 1;
  }
  return a;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  memset(dp, 0, NM * sizeof(l));

  dp[0][0] = 1;
  for (l i = 1; i < N; i++) {
    for (l j = 0; j < M && j <= i * 9; j++) {
      for (l k = 0; k <= 9 && k <= j; k++) {
        dp[i][j] += dp[i - 1][j - k];
      }
    }
  }

  scanf("%lld%lld%lld", &a, &b, &s);
  printf("%lld\n%lld\n", upper(b, s) - upper(a - 1, s), first(a - 1, s));
}
