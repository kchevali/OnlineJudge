#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

l n, m;

const l N = 1000 + 10, inf = 0x3f3f3f3f3f3f3f3f;
l parent[N], depth[N];
vector<l> adj[N];

// Complexity O(V+E)
void dfs(l a) {
  for (auto &b : adj[a]) {
    // cout << a << " " << b << "\n";
    if (depth[a] + 1 < depth[b]) {
      parent[b] = a;
      depth[b] = depth[a] + 1;
      // if (depth[b] > depth[maxDistIndex]) maxDistIndex = b; //get tree diameter
      dfs(b);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l t;
  cin >> t;
  for (l i = 0; i < t; i++) {
    cin >> n >> m;
    memset(depth, 0x3f, sizeof(depth));
    for (l j = 0; j < n; j++) adj[j] = vl();
    for (l j = 0; j < m; j++) {
      l a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    l count = 0;
    for (l j = 0; j < n; j++) {
      if (depth[j] == inf) {
        depth[j] = 0;
        count++;
        dfs(j);
      }
    }
    cout << (count - 1) << "\n";
  }
}
