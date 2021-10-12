#include <bits/stdc++.h>
using namespace std;
typedef long long l;

// BFS: Unweighted - find path from one source
const l N = 1e5 + 10, inf = 0x3f3f3f3f3f3f3f3f;
l parent[N], depth[N], domCount = 0;
vector<l> adj[N];
// Complexity O(V+E)
void bfs(l src) {
  queue<l> q;
  q.push(parent[src] = src);
  // depth = unordered_map<l, l>();//for freq depth reset use unordered_map
  depth[src] = 1;  // init depth to inf
  while (!q.empty()) {
    l a = q.front();
    q.pop();
    domCount++;
    for (l b : adj[a]) {
      if (depth[a] + 1 < depth[b]) {
        depth[b] = 1, parent[b] = a, q.push(b);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l tt;
  cin >> tt;
  while(tt--){
    l n, m, k;
    cin >> n >> m >> k;
    memset(depth,0x3f,sizeof(l)*n);
    for (l j = 0; j < n; j++) adj[j] = vector<l>();
    for(l i = 0; i < m; i++){
      l x, y;
      cin >> x >> y;
      adj[x-1].push_back(y-1);
    }
    domCount = 0;
    for(l i = 0; i < k; i++){
      l x;
      cin >> x;
      x--;
      if(depth[x] == inf){
        bfs(x);
      }
    }
    cout << domCount << "\n";

  }
}
