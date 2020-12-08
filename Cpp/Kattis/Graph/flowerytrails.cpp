#include <bits/stdc++.h>
using namespace std;
typedef long long l;

// Main:
typedef pair<l, l> ll;
typedef tuple<l, l, l> lll;
typedef vector<l> vl;
typedef vector<ll> vll;
typedef vector<lll> vlll;
const l N = 1e4 + 10, M = 25e4 + 10;
vector<pair<l, l>> pAdj[N];
l depth[N];
vlll parent[N];
bool vis[M];

// Complexity: O(V + E*log(V))
void dijkstra(l src, l dest) {
  priority_queue<ll, vll, greater<ll>> pq;  // w, node
  pq.push(make_pair(depth[src] = 0, src));
  l edgeIndex = 0;
  while (!pq.empty()) {
    ll curr = pq.top();
    pq.pop();
    l a = curr.second;
    if (a == dest) return;  // remove dest to explore all
    if (vis[a]) continue;
    vis[a] = true;
    for (auto& [w, b] : pAdj[a]) {
      if (!vis[b]) {
        l da = w + depth[a], &db = depth[b];
        if (da <= db) {
          if (da < db) parent[b] = vlll();
          parent[b].push_back({w, a, edgeIndex++});
          pq.push(make_pair((db = da), b));
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m;
  scanf("%lld%lld", &n, &m);
  for (l i = 0; i < m; i++) {
    l a, b, w;
    scanf("%lld%lld%lld", &a, &b, &w);
    pAdj[a].push_back({w, b});
    pAdj[b].push_back({w, a});
  }
  memset(depth, 0x3f, sizeof(l) * n);
  memset(vis, 0, sizeof(bool) * n);
  dijkstra(0, n - 1);
  memset(vis, 0, sizeof(bool) * m);

  queue<ll> q;
  q.push({0, n - 1});
  l total = 0;
  while (!q.empty()) {
    auto& [w, a] = q.front();
    q.pop();
    total += w;
    for (auto& [w, b, i] : parent[a]) {
      if (!vis[i]) {
        vis[i] = true;
        // vis[p.second] = true;
        q.push({w, b});
      }
    }
  }
  printf("%lld\n", total * 2);
}
