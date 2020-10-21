#include "../all.cpp"

l factorial(l n) { return n < 2 ? n : factorial(n - 1) * n; }
l permutation(l n) { return factorial(n); }

// binomial/combinations/pascal triangle
//=n!/((n-k)!k!)
l dp[1000][1000];
l binomial(l n, l k) {
  if (k > n) return 0;
  if (k == 0 || n == k) return 1;
  if (dp[n][k] >= 0) return dp[n][k];
  return dp[n][k] = binomial(n - 1, k - 1) + binomial(n - 1, k);
}

// ex: num of valid arrangements of parenthesis of n pairs
// num  of arrangements in a binary tree of n leaves
// num of triangular partitions of a polygon
l catalanNumbers(l n) { return n == 0 ? 1 : binomial(2 * n, n) / (n + 1); }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, m;
  for (l i = 0; i < 1000; i++)
    for (l j = 0; j < 1000; j++) dp[i][j] = -1;
  while (cin >> n >> m) cout << binomial(n, m) << "\n";
  //   for (l i = 0; i < 499; i++) cout << catalanNumbers(i) << "\n";
}
