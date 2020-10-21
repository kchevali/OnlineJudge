#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;
#define inf 0x3f3f3f3fLL

void bfs_single(l root, vector<vl> &adj, vl &prev, vl &depth) {
  queue<l> q;
  q.push(prev[root] = root);
  depth[root] = 1;  // init depth to inf
  while (!q.empty()) {
    l a = q.front();
    q.pop();
    for (l b : adj[a])
      if (depth[a] + 1 < depth[b]) {
        depth[b] = depth[a] + 1;
        prev[b] = a;
        q.push(b);
      }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, e;
  cin >> n >> e;
  vector<vl> adj(n);

  for (l i = 0; i < e; i++) {
    l a, b;
    cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adj[b - 1].push_back(a - 1);
  }

  vl prev(n), depth(n, inf);
  bfs_single(0, adj, prev, depth);
  cout << depth[n - 1] - 2 << "\n";
}
