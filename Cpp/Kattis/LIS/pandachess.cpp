#include <bits/stdc++.h>
#define L_INF 0x3f3f3f3f3f3f3f3f
#define PB emplace_back
#define MP make_pair
#define MT make_tuple
#define MID(x, y) x + (y - x) / 2
#define F first
#define S second
#define I cin >>
#define C cout <<
#define E << endl
#define _ << "\t" <<
#define fpp(i, a, b) for (i = a; i < b; i++)
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

void dfs2(l a, vvl &adj, vl &d, l &t) {
  d[a] = 0;
  for (l b : adj[a])
    if (d[b] < 0) dfs2(b, adj, d, t);
  d[a] = t++ - 1;
}

vl dfs(vvl &adj) {
  l i, t = 1;
  vl d = vl(adj.size(), -1);
  fpp(i, 0, adj.size()) {
    if (d[i] < 0) dfs2(i, adj, d, t);
  }
  return d;
}

l LIS2(vl &v) {
  if (v.size() == 0) return 0;
  vl dp = vl(v.size(), 0);
  dp[0] = v[0];
  l x = 1, i;
  fpp(i, 1, v.size()) {
    l a = 0, b = x - 1;
    while (a <= b) {
      l m = MID(a, b);
      if (dp[m] < v[i])
        a = m + 1;
      else
        b = m - 1;
    }
    dp[a] = v[i];
    x = max(x, a + 1);
  }
  return x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, m, d, i, j, k, t = 0;
  I n >> m >> d;
  auto mp = map<string, l>();
  vvl adj = vvl(n, vl());
  fpp(i, 0, m) {
    string a, b;
    l ak, bk;
    I a >> b;
    auto ai = mp.find(a), bi = mp.find(b);

    if (ai == mp.end()) {
      mp[a] = ak = t++;
    } else {
      ak = ai->S;
    }
    if (bi == mp.end()) {
      mp[b] = bk = t++;
    } else {
      bk = bi->S;
    }
    adj[bk].PB(ak);
  }
  vl endTimes = dfs(adj);
  string s;
  vl arr = vl();
  fpp(i, 0, n) {
    I s;
    auto si = mp.find(s);
    if (si != mp.end()) {
      arr.PB(endTimes[si->S]);
    }
  }
  l x = n - LIS2(arr);
  // ARR(arr);
  C(2 * x) E;
}
/*
4 4 3
345 678
12 345
345 678
678 999
1
345
999
345

2 1 0
0 1
1
0

4 3 0
0 1
1 2
2 3
5
5
5
5

*/