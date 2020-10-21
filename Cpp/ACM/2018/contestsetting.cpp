#include "../../all.cpp"

vl freq;
vvl dp;

l f(l i, l j) {
  if (j == 0) return 1;
  if (i == 0) return 0;
  if (dp[i][j] != -1) return dp[i][j];
  return dp[i][j] =
             (((freq[i - 1] * f(i - 1, j - 1)) % 998244353LL) + f(i - 1, j)) %
             998244353LL;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, k, i, x;
  cin >> n >> k;
  dp = vvl(n + 1, vl(k + 1, -1));

  map<l, l> mp;
  freq = vl(n);
  l index = 1;
  fpp(i, 0, n) {
    cin >> x;
    if (mp[x] == 0) mp[x] = index++;
    freq[mp[x] - 1]++;
  }
  C f(n, k) E;
}
