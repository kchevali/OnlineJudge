#include <bits/stdc++.h>
using namespace std;
typedef long long l;

typedef pair<l, l> ll;
typedef vector<ll> vll;
#define iinf 0x3f3f3f3fLL

const l N = 1001;
vll adj[N];
l dist[N];
bool isNeg[N];

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
void bellmanFord(l src, l n) {
  for (l i = 0; i < n; i++) {
    dist[i] = iinf;
    isNeg[i] = false;
  }
  dist[src] = 0;

  for (l i = 1; i < n; i++)
    for (l a = 0; a < n; a++)
      if (dist[a] != iinf)
        for (l j = 0; j < adj[a].size(); j++) {
          l b = adj[a][j].second;
          l w = adj[a][j].first;
          dist[b] = min(dist[a] + w, dist[b]);
        }

  bool isDone = false;
  while (!isDone) {
    isDone = true;
    for (l a = 0; a < n; a++) {
      if (dist[a] == iinf) continue;
      for (l i = 0; i < adj[a].size(); i++) {
        l b = adj[a][i].second;
        l w = adj[a][i].first;
        if (dist[a] + w < dist[b] && !isNeg[b]) {
          isNeg[b] = true;
          isDone = false;
          dist[b] = -iinf;
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (true) {
    l n, m, qs, s;
    cin >> n >> m >> qs >> s;
    if (n == 0 && m == 0 && qs == 0 && s == 0) break;
    for (l i = 0; i < n; i++) adj[i] = vll();
    for (l i = 0; i < m; i++) {
      l a, b, w;
      cin >> a >> b >> w;
      adj[a].emplace_back(make_pair(w, b));
    }
    bellmanFord(s, n);
    for (l i = 0; i < qs; i++) {
      l q;
      cin >> q;
      cout << (isNeg[q] ? "-Infinity"
                        : dist[q] == iinf ? "Impossible" : to_string(dist[q]))
           << "\n";
    }
    cout << "\n";
  }
}
