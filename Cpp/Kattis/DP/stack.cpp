#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
using namespace std;
typedef long long l;
typedef v(l) vl;
typedef v(vl) vvl;

string s;
l N;
vvl dp;

l a(l i, l j) {
  if (i > j) return 0;
  if (dp[i][j] != -1) return dp[i][j];
  l k, mn = 2 + a(i, j - 1);
  fpp(k, i, j) if (s[k] == s[j]) mn = min(mn, a(i, k) + a(k + 1, j - 1));
  return dp[i][j] = mn;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, i, j, k;
  cin >> n;
  cin.ignore();
  fpp(i, 0, n) {
    getline(cin, s);
    N = s.length();
    dp = vvl(N, vl(N, -1));

    C(N + a(0, s.length() - 1)) E;
  }
}
