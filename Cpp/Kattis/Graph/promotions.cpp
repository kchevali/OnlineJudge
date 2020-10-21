#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define fpp(i, a, b) for (i = a; i < b; i++)
#define v(t) vector<t>
using namespace std;
typedef long long l;

typedef v(l) vl;
typedef v(vl) vvl;

l dfs_single(l a, vvl &adj, vl &vis) {
  vis[a >> 6LL] |= (1LL << (a & 63LL));
  l count = 0;
  for (auto b : adj[a])
    if ((vis[b >> 6LL] & (1LL << (b & 63LL))) == 0)
      count += dfs_single(b, adj, vis) + 1;
  return count;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l a, b, e, p, i, j, x, y, aa = 0, bb = 0, cc = 0;

  cin >> a >> b >> e >> p;
  vvl adj = vvl(e, vl()), inv_adj = vvl(e, vl());
  fpp(i, 0, p) {
    cin >> x >> y;
    adj[x].PB(y);
    inv_adj[y].PB(x);
  }
  vl minDepths = vl(e, 0), maxDepths = vl(e, 0);
  fpp(i, 0, e) {
    vl vis = vl((e >> 6) + 1, 0);
    l parents = dfs_single(i, inv_adj, vis);
    l children = dfs_single(i, adj, vis);
    minDepths[i] = parents + 1;
    maxDepths[i] = e - children;
  }
  fpp(i, 0, e) {
    if (a >= maxDepths[i]) aa++;
    if (b >= maxDepths[i]) bb++;
    if (b < minDepths[i]) cc++;
  }
  C aa << "\n" << bb << "\n" << cc E;
}

/*
5 8 9 9
0 1
1 2
2 3
3 4
4 5
5 6
6 7
6 8
0 7


1 2 6 6
0 3
1 3
2 3
1 4
2 4
2 5

1 2 4 2
0 1
1 2
 */