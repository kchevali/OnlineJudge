#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << endl
#define _ << " " <<
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define linf 0x3f3f3f3f3f3f3f3f

using namespace std;
typedef long long l;
typedef pair<l, l> ll;
typedef vector<l> vl;
typedef vector<vl> vvl;
typedef vector<ll> vll;
typedef vector<vll> vvll;

vvl v;
l n, c;
vvll dp;
ll search(l curr, l left) {
  if (left == 0) return (ll){0, 0};
  if (dp[curr][left].first != -1) return dp[curr][left];
  l i, j, x = 0, y = linf;
  fpp(i, 0, n) {
    l a, b;
    tie(a, b) = search(i, left - 1);
    x = max(x, v[curr][i] + a);
    y = min(y, v[curr][i] + b);
  };
  dp[curr][left].first = x;
  dp[curr][left].second = y;

  return dp[curr][left];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l i, j;
  cin >> n;
  while (n > 0) {
    v = vvl(n, vl(n, 0));  //[go][current]
    fpp(i, 0, n) {
      fpp(j, 0, n) { cin >> v[i][j]; }
    }
    cin >> c;
    dp = vvll(n, vll(c, make_pair(-1, -1)));
    tie(i, j) = search(0, c);
    C i _ j E;
    cin >> n;
  }
}
