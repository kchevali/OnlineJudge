#include <bits/stdc++.h>
using namespace std;
typedef long long l;

typedef vector<pair<l, l>> vll;
const l N = 30 + 5, inf = 0x3f3f3f3f3f3f3f3f;
vll pAdj[N * N];
l depth[N * N], grid[N][N];
bool isNeg[N * N], negCycle;
l dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1};

// Complexity: O(V*E)
void bellmanFord(l src, l n) {
  memset(depth, 0x3f, sizeof(l) * n);
  memset(isNeg, 0, sizeof(bool) * n);
  depth[src] = 0;
  for (l i = 1; i < n; i++)
    for (l a = 0; a < n; a++) {
      if (depth[a] != inf)
        for (auto &[w, b] : pAdj[a]) {
          depth[b] = min(depth[a] + w, depth[b]);
        }
    }

  bool isDone = false;
  while (!isDone) {
    isDone = true;
    for (l a = 0; a < n; a++) {
      if (depth[a] == inf) continue;
      for (auto &[w, b] : pAdj[a]) {
        if (depth[a] + w < depth[b] && !isNeg[b]) {
          isNeg[b] = true;
          isDone = false;
          depth[b] = -inf;
          negCycle = true;
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l w, h;
  while (scanf("%lld%lld", &w, &h) != EOF && w > 0) {
    l n = h * w;
    negCycle = false;
    for (l i = 0; i < w; i++)
      for (l j = 0; j < h; j++) grid[i][j] = 0;
    for (l i = w * h; i-- > 0;) pAdj[i] = vll();
    l g;
    scanf("%lld", &g);
    for (l i = 0; i < g; i++) {
      l x, y;
      scanf("%lld%lld", &x, &y);
      grid[x][y] = -1;
    }

    l e;
    scanf("%lld", &e);
    for (l i = 0; i < e; i++) {
      l x1, y1, x2, y2, t;
      scanf("%lld%lld%lld%lld%lld", &x1, &y1, &x2, &y2, &t);
      l a = x1 + y1 * w, b = x2 + y2 * w;
      grid[x1][y1] = i + 1;
      pAdj[a].push_back(make_pair(t, b));
    }

    for (l i = 0; i < w; i++) {
      for (l j = 0; j < h; j++) {
        l a = i + j * w;
        if (grid[i][j] == 0 && a != n - 1) {
          for (l k = 0; k < 4; k++) {
            l x = i + dx[k], y = j + dy[k];
            if (grid[x][y] >= 0 && x >= 0 && y >= 0 && x < w && y < h) {
              pAdj[a].push_back(make_pair(1, x + y * w));
            }
          }
        }
      }
    }
    bellmanFord(0, w * h);
    printf("%s\n", (negCycle ? "Never" : (depth[n - 1] == inf ? "Impossible" : to_string(depth[n - 1]).c_str())));
  }
}
