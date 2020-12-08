#include <bits/stdc++.h>
using namespace std;
typedef long long l;

struct edge {
  double w;
  l a, b;
  edge(double w, l a, l b) : a(a), b(b), w(w) {}
  bool operator<(const struct edge &other) const { return w > other.w; }
};

const l N = 750 + 10;
vector<pair<double, l>> pAdj[N];
bool vis[N];
double x[N], y[N];
vector<edge> result;
// Main:
// Complexity: O(E*log(V))
double prim_mst(l src) {
  double weight = 0;
  vis[src] = true;
  priority_queue<edge, vector<edge>, less<edge>> q;
  for (auto &[w, b] : pAdj[src]) {
    q.push(edge(w, src, b));
  }

  while (!q.empty()) {
    const edge e = q.top();
    auto &[w, a, b] = e;
    q.pop();

    if (!vis[b]) {
      vis[b] = true;
      weight += w;
      result.push_back(e);  // store the MST
      for (auto &[w2, c] : pAdj[b]) {
        if (!vis[c]) q.push(edge(w2, b, c));
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
    l n;
    scanf("%lld", &n);
    memset(vis, 0, sizeof(bool) * n);
    for (l j = 0; j < n; j++) pAdj[j] = vector<pair<double, l>>();
    for (l j = 0; j < n; j++) {
      scanf("%lf%lf", x + j, y + j);
      for (l k = 0; k < j; k++) {
        double dx = x[j] - x[k], dy = y[j] - y[k];
        double dist = sqrt(dx * dx + dy * dy);
        pAdj[j].push_back({dist, k});
        pAdj[k].push_back({dist, j});
      }
    }
    printf("%lf\n", prim_mst(0));
  }
}
