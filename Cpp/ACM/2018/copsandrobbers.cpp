#include "../../all.cpp"

const l N = 30;
char grid[N][N];
l cost[26];

l cap[2 * N - 1][2 * N - 1];

// Maximum Flow (Ford-Fulkerson Algorithm) O(VE2) - Undirected: One sink and
// source, non negative weights BFS Version:
bool bfsMod(l src, l dest, vvl &resi, map<l, l> &parent) {
  vl vis(resi.size(), false);
  ql q;
  q.push(src);
  vis[src] = true;
  while (!q.empty()) {
    l a = q.front();
    q.pop();
    for (l b = 0; b < resi.size(); b++) {
      if (!vis[b] && resi[a][b] > 0) {
        parent[b] = a;
        vis[b] = true;
        q.push(b);

        if (b == dest) return true;
      }
    }
  }
  return false;
}

l bfsMaxFlow(l src, l dest, vvl cap) {
  vvl resi(cap.size(), vl(cap[0].size(), 0));
  l i, j;
  fpp(i, 0, cap.size()) { fpp(j, 0, cap[0].size()) resi[i][j] = cap[i][j]; }

  map<l, l> parent;
  vvl augPath;  // Paths are stored here

  l maxFlow = 0;

  while (bfsMod(src, dest, resi, parent)) {
    vl augmentedPath;
    l flow = linf;

    l v = dest;
    while (v != src) {
      augmentedPath.PB(v);
      l u = parent[v];
      flow = min(flow, resi[u][v]);
      v = u;
    }
    augmentedPath.PB(src);
    reverse(augmentedPath.begin(), augmentedPath.end());
    augPath.PB(augmentedPath);

    maxFlow += flow;

    v = dest;
    while (v != src) {
      l u = parent[v];
      resi[u][v] -= flow;
      resi[v][u] += flow;
      v = u;
    }
  }
  return maxFlow;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l w, h, c;
  cin >> w >> h >> c;
  for (l i = 0; i < h; i++) {
    for (l j = 0; j < w; j++) {
      cin >> grid[i][j];
    }
  }
  for (l i = 0; i < c; i++) cin >> cost[i];

  l W = 2 * w - 1, H = 2 * h - 1;
  for (l i = 0; i < h; i++) {
    for (l j = 0; j < w; j++) {
      l x =
    }
  }
}