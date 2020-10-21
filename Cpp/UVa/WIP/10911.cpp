#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef pair<l, l> ll;
#define dc(x) fixed << setprecision(x)

const l N = 16, N_ = 1 << 16;
ll nums[N];
string s;
double dp[N_];
double COST[N][N];
l n;

double cost(l a, l b) {
  // if (COST[a][b] != -1.0) return COST[a][b];
  double dx = nums[a].first - nums[b].first;
  double dy = nums[a].second - nums[b].second;
  return COST[a][b] = COST[b][a] = sqrt(dx * dx + dy * dy);
}

double solve(l vis) {
  // cout << vis << " " << dp[vis] << "\n";
  if (dp[vis] != -1) return dp[vis];
  if (vis == (1 << n) - 1) return dp[vis] = 0;
  double mn = 1e9;
  for (l i = 0; i < n; i++) {
    l i_ = 1 << i;
    for (l j = i + 1; j < n; j++) {
      l j_ = 1 << j;
      if ((vis & i_) == 0 && (vis & j_) == 0) {
        vis |= i_ | j_;
        double ans = solve(vis), c = cost(i, j);
        vis &= ~(i_ | j_);
        mn = min(ans + c, mn);
        // cout << i << " " << j << " " << ans << " " << c << " a: " << mn << "\n";
      }
    }
  }
  return dp[vis] = mn;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l c = 1;
  while (cin >> n && n > 0) {
    n *= 2;
    for (l i = 0; i < n; i++) {
      cin >> s >> nums[i].first >> nums[i].second;
    }
    for (l i = 0; i < N_; i++) dp[i] = -1;

    for (l i = 0; i < N; i++)
      for (l j = 0; j < N; j++) COST[i][j] = -1.0;

    cout << "Case " << (c++) << ": " << dc(2) << solve(0) << "\n";
  }
}
