#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;
#define inf 0x3f3f3f3fLL

// BFS: Unweighted - find path
// find path from single source
void bfs_single(l root, vector<vl> &adj, vl &prev, vl &depth) {
  queue<l> q;
  q.push(prev[root] = root);
  depth[root] = 0;
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

  l h, w, n;
  cin >> h >> w;
  n = h * w;

  l dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  vector<vl> grid(n);
  vl prev(n, 0), depth(n, inf);

  for (l i = 0; i < h; i++) {
    string s;
    cin >> s;

    for (l j = 0; j < w; j++) {
      l index = i * w + j, num = s[j] - '0';
      for (auto &d : dir) {
        l x = j + d[0] * num, y = i + d[1] * num;
        l index1 = y * w + x;
        if (x >= 0 && x < w && y >= 0 && y < h) {
          grid[index].push_back(index1);
        }
      }
    }
  }
  bfs_single(0, grid, prev, depth);
  cout << (depth[n - 1] == inf ? -1 : depth[n - 1]) << "\n";
  l node = n - 1;
  while (node != 0) {
    cout << "Node: " << node << "\n";
    node = prev[node];
  }
}

// 249,999