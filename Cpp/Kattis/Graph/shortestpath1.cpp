#include <bits/stdc++.h>
using namespace std;
typedef long long l;
#define iinf 0x3f3f3f3f

typedef pair<l, l> ll;
typedef vector<l> vl;
typedef vector<ll> vll;

const l N = 10001;
vll adj[N];
l dis[N];
bool vis[N];

void dijkstra(l source, l n) {
  for (l i = 0; i < n; i++) {
    dis[i] = iinf;
    vis[i] = 0;
  }
  priority_queue<ll, vll, greater<ll> > pq;
  pq.push(make_pair(dis[source] = 0, source));
  while (!pq.empty()) {
    ll curr = pq.top();
    pq.pop();
    l a = curr.second;
    if (vis[a]) continue;
    vis[a] = true;
    for (l i = 0; i < adj[a].size(); i++) {
      l b = adj[a][i].second, w = adj[a][i].first;
      if (!vis[b] && w + dis[a] < dis[b]) {
        pq.push(make_pair((dis[b] = w + dis[a]), b));
      }
    }
  }
}

int main() {
  l n, m, q, s;
  l x, y, w;
  while (true) {
    cin >> n >> m >> q >> s;
    if (n == 0 && m == 0 && q == 0 && s == 0) break;
    for (l i = 0; i < n; i++) adj[i] = vll();
    for (l i = 0; i < m; i++) {
      cin >> x >> y >> w;
      adj[x].push_back(make_pair(w, y));
    }
    dijkstra(s, n);
    for (l i = 0; i < q; i++) {
      l num;
      cin >> num;
      if (dis[num] >= iinf)
        printf("Impossible\n");
      else
        printf("%lld\n", dis[num]);
    }
    cout << "\n";
  }
  return 0;
}