#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;
#define inf 0x3f3f3f3fLL

l maxDistIndex = 0;
void dfs_single(l a, vector<vl> &adj, vl &prev, vl &depth) {
  for (auto &b : adj[a]) {
    // cout << "DFS2: " << a << " " << b << " D: " << depth[a] << " " << depth[b] << "\n";
    if (depth[a] + 1 < depth[b]) {
      prev[b] = a;
      depth[b] = depth[a] + 1;
      // cout << "DFS: " << a << " " << b << " D: " << depth[a] << " " << depth[b] << "\n";
      if (depth[b] > depth[maxDistIndex]) maxDistIndex = b;  // get tree diameter
      dfs_single(b, adj, prev, depth);
    }
  }
}

l get_tree_diameter(l src, vector<vl> &adj) {
  // cout << "SRC: " << src << "\n";
  vl prev(adj.size(), 0), depth(adj.size(), inf);
  depth[maxDistIndex = src] = 0;
  dfs_single(src, adj, prev, depth);
  // cout << "Greatest Depth: " << maxDistIndex << "\n";
  for (l i = 0; i < adj.size(); i++) depth[i] = inf;
  depth[maxDistIndex] = 0;
  // cout << "RESET: " << maxDistIndex << "\n";
  dfs_single(maxDistIndex, adj, prev, depth);
  // cout << "Greatest Depth: " << maxDistIndex << "\n";
  // cout << "LENGTH: " << depth[maxDistIndex] << "\n";
  return depth[maxDistIndex];
}

vl p, ranks, setSize;
l numSets;  // the number of disjoint sets
l findSet(l i) { return p[i] == i ? i : p[i] = findSet(p[i]); }
// return true if element i and j are in the same set, return false otherwise
bool isSameSet(l i, l j) { return findSet(i) == findSet(j); }
// union two sets that contain element i and j
void unionSet(l i, l j) {
  l x = findSet(i), y = findSet(j);
  if (x == y) return;
  // ranks is used to keep the tree short
  if (ranks[x] > ranks[y]) {
    p[y] = x;
    setSize[x] += setSize[y];
  } else {
    p[x] = y;
    setSize[y] += setSize[x];
    if (ranks[x] == ranks[y]) ranks[y]++;
  }
}
// return the size of the set that contain element i
l sizeOfSet(l i) { return setSize[findSet(i)]; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m;
  cin >> n >> m;
  vector<vl> adj(n);
  p = vl(n);
  ranks = vl(n, 0);
  iota(p.begin(), p.end(), 0);
  setSize = vl(n, 0);
  for (l i = 0; i < m; i++) {
    l a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    unionSet(a, b);
  }

  l total = get_tree_diameter(0, adj) / 2, maxTotal = 0;
  for (l i = 0; i < n; i++) {
    if (!isSameSet(0, i)) {
      l length = get_tree_diameter(i, adj);
      total += length / 2 + 1;  //(length & 1);
      maxTotal = max(maxTotal, length);
      unionSet(0, i);
    }
  }

  cout << (max(maxTotal, total)) << "\n";
}  // 2 1 0 4 5
   // 8 7 9

/*
3 2
0 1
1 2

6 5
0 1
0 2
0 3
3 4
3 5
*/