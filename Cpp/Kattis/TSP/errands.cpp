// https://open.kattis.com/problems/errands
// DP TSP problem

#include <bits/stdc++.h>
using namespace std;
typedef long long l;

const l N = 100 + 10, inf = 1e17, mN = 12 + 3;
string places[N];
double xs[N], ys[N], dis[mN][mN], dp[(1 << mN) - 1][mN];
l path[mN], nums[mN], n, m;
unordered_map<string, l> mp;

l cmp(double a, double b) { return fabs(a - b) < 1e-6 ? 0 : a < b ? -1 : 1; }

// Complexity: O(2^n * n^2)
// Input: vis(bits to 1), a(starting index - not include in vis)
double tsp(l vis, l a) {
  if (vis == 0) return dp[vis][a] = dis[a][1];
  if (cmp(dp[vis][a], -1) != 0) return dp[vis][a];

  double cost = inf;
  for (l b = 2, bit = 1; b < m; b++, bit <<= 1) {
    if ((vis & bit) != 0) {
      cost = min(cost, dis[a][b] + tsp(vis - bit, b));
    }
  }
  return dp[vis][a] = cost;
}

// Complexity: O(n)
bool tspPath(l vis, l a, l depth) {
  // cout << "P:";
  // db(vis, a, depth);
  if (vis == 0) return true;
  for (l b = 2, bit = 1; b < m; b++, bit <<= 1) {
    l nextVis = vis - bit;
    if (cmp(dp[vis][a], dis[a][b] + dp[nextVis][b]) == 0 && tspPath(nextVis, b, depth + 1)) {
      path[depth] = b;
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  bool seeHome = false, seeWork = false, hasDup = false;

  cin >> n;
  for (l i = 2; i < n || !seeHome || !seeWork; i++) {
    double x, y;
    cin >> places[i] >> x >> y;
    l index = places[i] == "home" ? 1 : (places[i] == "work" ? 0 : i);
    seeHome = seeHome || index == 1;
    seeWork = seeWork || index == 0;
    if (index < 2) places[index] = places[i--];
    xs[index] = x, ys[index] = y;  //(l)(x * 1e5), ys[index] = (l)(y * 1e5)
    mp[places[index]] = index;
  }
  assert(seeHome && seeWork && "MISSING DATA");
  // for (l i = 0; i < n; i++) {
  //   cout << places[i] << " " << xs[i] << ", " << ys[i] << "\n";
  // }

  string line, token;
  nums[0] = 0, nums[1] = 1;
  cin.ignore();
  while (getline(cin, line)) {
    stringstream ss(line);
    for (m = 2; ss >> token; m++) nums[m] = mp[token];
    for (l i = (1 << (m - 2)) - 1; i >= 0; i--) {
      for (l j = 0; j < m; j++) {
        dp[i][j] = -1.0;
      }
    }
    for (l i = 0; i < m; i++) {
      for (l j = i + 1; j < m; j++) {
        l dx = (xs[nums[i]] - xs[nums[j]]), dy = (ys[nums[i]] - ys[nums[j]]);
        dis[i][j] = dis[j][i] = sqrt(dx * dx + dy * dy);
      }
    }
    l vis = (1 << (m - 2)) - 1;
    tsp(vis, 0);
    assert(tspPath(vis, 0, 0) && "ERROR");
    for (l i = 0; i < m - 2; i++) cout << places[nums[path[i]]] << " ";
    cout << "\n";
  }
}
