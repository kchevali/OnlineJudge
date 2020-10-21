#include <bits/stdc++.h>
using namespace std;
typedef long long l;
#define gc getchar_unlocked
#define iinf 0x3f3f3f3f

void read(l& x) {
  l c = gc();
  x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc())
    ;
  if (c == '-') {
    neg = 1;
    c = gc();
  }
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
  if (neg) x = -x;
}
struct edge {
  l b, t0, interval, d;
};
typedef pair<l, l> ll;
typedef vector<ll> vll;
typedef vector<edge> vedge;

const l N = 10001;
vedge adj[N];
l dis[N];
bool vis[N];

void dijkstra(l source, l n) {
  for (l i = 0; i < n; i++) {
    dis[i] = iinf;
    vis[i] = 0;
  }
  priority_queue<ll, vll, greater<ll> > pq;  // w, node
  pq.push(make_pair(dis[source] = 0, source));
  while (!pq.empty()) {
    ll curr = pq.top();
    pq.pop();
    l a = curr.second;
    if (vis[a]) continue;
    vis[a] = true;
    for (l i = 0; i < adj[a].size(); i++) {
      l b = adj[a][i].b, t0 = adj[a][i].t0, it = adj[a][i].interval,
        d = adj[a][i].d, t = dis[a];

      if (it != 0)
        t = it * ((l)ceil(((double)(max(t, t0) - t0) / it))) + t0;
      else if (t <= t0)
        t = t0;
      else
        continue;
      if (!vis[b] && d + t < dis[b]) pq.push(make_pair((dis[b] = d + t), b));
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  while (true) {
    l n, m, qs, src, q, a;
    read(n);
    read(m);
    read(qs);
    read(src);
    if (n == 0 && m == 0 && qs == 0 && src == 0) break;
    for (int i = 0; i < n; i++) adj[i] = vedge();
    for (l i = 0; i < m; i++) {
      struct edge p;
      read(a);
      read(p.b);
      read(p.t0);
      read(p.interval);
      read(p.d);
      adj[a].emplace_back(p);
    }
    dijkstra(src, n);
    for (l i = 0; i < qs; i++) {
      read(q);
      cout << (dis[q] == iinf ? "Impossible" : to_string(dis[q])) << "\n";
    }
    cout << "\n";
  }
}
