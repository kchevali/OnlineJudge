#include <bits/stdc++.h>
using namespace std;
typedef long long l;

const l L = 50, N = L * L + 10, inf = 1e18;
l h, w;

l parent[N], depth[N];
vector<l> adj[N];
string grid[L];
// Complexity O(V+E)
void bfs_single(l src) {
  queue<l> q;
  q.push(parent[src] = src);
  depth[src] = 1;  // init depth to inf
  while (!q.empty()) {
    l a = q.front();
    grid[a / w][a % w] = 'V';
    q.pop();
    for (l b : adj[a]) {
      if (depth[a] + 1 < depth[b]) {
        depth[b] = depth[a] + 1;
        parent[b] = a;
        q.push(b);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  memset(depth, 0x3f, sizeof(depth));
  cin >> h >> w;
  l n = h * w;
  for (l i = 0; i < h; i++) {
    cin >> grid[i];
  }
  for (l i = 0, index = 0; i < h - 1; i++) {
    for (l j = 0; j < w; j++, index++) {
      if (grid[i][j] == '.' || grid[i][j] == 'V') {
        if (grid[i + 1][j] == '.')
          adj[index].push_back(index + w);
        else if (grid[i + 1][j] == '#') {
          if (j > 0 && grid[i][j - 1] == '.') adj[index].push_back(index - 1);
          if (j < w - 1 && grid[i][j + 1] == '.') adj[index].push_back(index + 1);
        }
      }
    }
  }
  for (l i = 0, index = 0; i < h; i++) {
    for (l j = 0; j < w; j++, index++) {
      if (grid[i][j] == 'V') {
        bfs_single(index);
      }
    }
    cout << grid[i] << "\n";
  }
}
