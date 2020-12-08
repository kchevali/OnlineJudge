#include <bits/stdc++.h>
using namespace std;
typedef long long l;

struct edge {
  l a, b, w;
  edge(l a, l b, l w) : a(a), b(b), w(w) {}
  bool operator<(const struct edge& other) const { return w > other.w; }
};

typedef pair<l, l> ll;
typedef tuple<l, l, l> lll;

const l N = 2000 + 10;
vector<lll> adj[N];
bool vis[N];
l prim_mst(l src, l n) {
  double weight = 0;
  memset(vis, 0, sizeof(bool) * n);
  priority_queue<edge> q;

  vis[src] = true;
  for (auto& [w1, a1, b1] : adj[src]) {
    // db(w1, a1, b1);
    q.push(edge(a1, b1, w1));
  }

  while (!q.empty()) {
    edge e = q.top();
    q.pop();

    if (!vis[e.b]) {
      weight += e.w;
      // db(e.w, e.a, e.b);
      vis[e.b] = true;
      for (auto& [w, a, b] : adj[e.b]) {
        if (!vis[b]) {
          q.push(edge(a, b, w));
        }
      }
    }
  }
  return weight;  // return MST
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l t;
  scanf("%lld", &t);
  for (l i = 0; i < t; i++) {
    l m, n;
    scanf("%lld%lld", &m, &n);
    for (l i = 0; i < n; i++) adj[i] = vector<lll>();
    for (l j = n * (n - 1) / 2; j-- > 0;) {
      l a, b, w;
      scanf("%lld%lld%lld", &a, &b, &w);
      adj[a].push_back({w, a, b});
      adj[b].push_back({w, b, a});
    }
    l cost = prim_mst(0, n);
    // printf("%lld\n", cost + n);
    printf("%s\n", cost + n <= m ? "yes" : "no");
  }
}
