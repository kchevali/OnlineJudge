#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef tuple<int, l, l> edge;  // node, cap, flow
typedef vector<l> vl;
typedef pair<l, l> ll;
const l inf = 1e18;

class MaxFlow {
 public:
  MaxFlow(l nodes) : n(nodes) {
    edges.clear();
    adj.assign(n, vl());
  }

  // directed means one way edge
  void addEdge(l a, l b, l cap, bool directed = true) {
    if (a == b) return;
    edges.emplace_back(b, cap, 0);
    adj[a].push_back(edges.size() - 1);
    edges.emplace_back(a, directed ? 0 : cap, 0);
    adj[b].push_back(edges.size() - 1);
  }

  // Complexity: O(V*E^2)
  l edmondsKarp(l s, l t) {
    l mf = 0;
    while (bfs(s, t)) {
      l f = sendOneFlow(s, t);
      if (f == 0) break;
      mf += f;
    }
    return mf;
  }
  // Complexity: O(V^2*E)
  l dinic(l s, l t) {
    l mf = 0;
    while (bfs(s, t)) {
      last.assign(n, 0);
      while (l f = dfs(s, t)) mf += f;
    }
    return mf;
  }

  vector<pair<l, edge>> getFlowEdges() {
    vector<pair<l, edge>> ans;
    for (l a = 0; a < n; a++) {
      for (l idx : adj[a]) {
        edge &e = edges[idx];
        if (get<2>(e) > 0) ans.emplace_back(make_pair(a, e));
      }
    }
    return ans;
  }

 private:
  bool bfs(l src, l dest) {
    d.assign(n, -1);
    d[src] = 0;
    queue<l> q({src});
    p.assign(n, {-1, -1});
    while (!q.empty()) {
      l a = q.front();
      q.pop();
      if (a == dest) break;
      for (auto &idx : adj[a]) {
        auto &[b, cap, flow] = edges[idx];
        if ((cap - flow > 0) && (d[b] == -1)) d[b] = d[a] + 1, q.push(b), p[b] = {a, idx};
      }
    }
    return d[dest] != -1;
  }

  l dfs(l a, l dest, l f = inf) {
    if ((a == dest) || (f == 0)) return f;
    for (l &i = last[a]; i < (l)adj[a].size(); i++) {
      auto &[b, cap, flow] = edges[adj[a][i]];
      if (d[b] != d[a] + 1) continue;
      if (l pushed = dfs(b, dest, min(f, cap - flow))) {
        flow += pushed;
        auto &rflow = get<2>(edges[adj[a][i] ^ 1]);
        rflow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  l sendOneFlow(l src, l dest, l f = inf) {
    if (src == dest) return f;
    auto &[a, idx] = p[dest];
    auto &cap = get<1>(edges[idx]), &flow = get<2>(edges[idx]);
    l pushed = sendOneFlow(src, a, min(f, cap - flow));
    flow += pushed;
    auto &rflow = get<2>(edges[idx ^ 1]);
    rflow -= pushed;
    return pushed;
  }

  l n;
  vector<edge> edges;
  vector<vl> adj;
  vl d, last;
  vector<ll> p;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m, s, t;
  scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
  MaxFlow flow(n);
  for (l i = 0; i < m; i++) {
    l a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    flow.addEdge(a, b, c);
  }
  l maxFlow = flow.dinic(s, t);
  auto edges = flow.getFlowEdges();
  l edgeCount = edges.size();

  printf("%lld %lld %lld\n", n, maxFlow, edgeCount);
  for (auto &[a, e] : edges) {
    printf("%lld %d %lld\n", a, get<0>(e), get<2>(e));
  }
}