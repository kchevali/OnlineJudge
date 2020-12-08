#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

const l H = 20 + 3, W = 60 + 3, N = 2 * H * W, inf = 0x3f3f3f3f3f3f3f3f;
typedef pair<l, l> ll;
typedef vector<l> vl;
typedef vector<ll> vll;

vector<pair<l, l>> pAdj[N];
l depth[N], parent[N];
bool vis[N];
string grid[H];
l dx[4] = {0, 1, 1, -1}, dy[4] = {1, 1, 0, 1};

void dijkstra(l src, l n) {
  memset(depth, 0x3f, sizeof(l) * n);
  memset(vis, 0, sizeof(bool) * n);
  priority_queue<ll, vll, greater<ll>> pq;  // w, node
  pq.push(make_pair(depth[src] = 0, src));
  while (!pq.empty()) {
    ll curr = pq.top();
    pq.pop();
    l a = curr.second;
    if (vis[a]) continue;
    vis[a] = true;
    for (auto &[w, b] : pAdj[a]) {
      if (!vis[b] && w + depth[a] < depth[b]) {
        parent[b] = a;
        pq.push(make_pair((depth[b] = w + depth[a]), b));
      }
    }
  }
}

l path[N];

// Complexity: O(n)
l getPath(l src, l dest) {
  l length = 0;
  while (src != dest) path[length++] = dest, dest = parent[dest];
  // std::reverse(path, path + i); //to start at src instead of dest
  return length;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l h, w, n;
  while (cin >> h >> w && h > 0) {
    n = 2 * (h * w + 1);
    for (l j = 0; j < n; j++) pAdj[j] = vll();

    for (l j = 0, index = 1; j < h; j++) {
      cin >> grid[j];
      for (l k = 0; k < w; k++, index++) {
        l a = 2 * index, b = a + 1, weight = grid[j][k] - '0';
        pAdj[a].push_back({weight, b});
        for (l m = 0; m < 4; m++) {
          l y = j + dy[m], x = k + dx[m], index2 = x + 1 + y * w, c = 2 * index2, d = c + 1;
          if (x >= 0 && y >= 0 && x < w && y < h) {
            pAdj[b].push_back({0, c});
            pAdj[d].push_back({0, a});
          }
        }
      }
    }

    for (l j = 1, k = n - 1; j <= w; j++, k -= 2) {
      pAdj[0].push_back({0, j * 2});
      pAdj[k].push_back({0, 1});
    }
    dijkstra(0, n);
    l length = getPath(0, 1);
    for (l j = 0; j < length; j++) {
      l p = path[j] / 2 - 1;
      if (p >= 0) {
        grid[p / w][p % w] = ' ';
      }
    }
    for (l j = 0; j < h; j++) cout << grid[j] << "\n";
  }
}
