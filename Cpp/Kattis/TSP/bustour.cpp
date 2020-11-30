#include <bits/stdc++.h>
using namespace std;
typedef int l;
#define count_bits __builtin_popcount

const l N = 20, inf = 1e9, H = N - 2;
l n, m;
l dp[1 << H][N][N], DIST[N][N];
void APSP() {
  for (l k = 0; k < n; k++)
    for (l i = 0; i < n; i++)
      for (l j = 0; j < n; j++)
        if (DIST[i][k] != inf && DIST[k][j] != inf) DIST[i][j] = min(DIST[i][j], DIST[i][k] + DIST[k][j]);
}

// hotels - hotel index only //a,b - node index
// go from a(not included) through hotels to b(not included)
l explore(l hotels, l a, l b) {
  if (hotels == 0) return DIST[a][b];
  l &x = dp[hotels][a][b];
  if (x != -1) return x;

  l cost = inf, mask = hotels;
  while (mask) {
    l bit = mask & (-mask);
    l i = __builtin_ctz(bit) + 1;
    cost = min(cost, DIST[a][i] + explore(hotels ^ bit, i, b));
    mask -= bit;
  }
  return x = cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l cases = 1;
  while (scanf("%d%d", &n, &m) != EOF) {
    memset(DIST, 0x3f, sizeof(l) * N * N);
    memset(dp, -1, sizeof(l) * (1LL << H) * N * N);
    l h = n - 2, allVis = (1LL << h) - 1;

    for (l i = 0; i < n; i++) DIST[i][i] = 0;
    for (l i = 0; i < m; i++) {
      l a, b, w;
      scanf("%d%d%d", &a, &b, &w);
      DIST[a][b] = w;
      DIST[b][a] = w;
    }
    APSP();
    l totalCost = inf, halfBits = h / 2;
    for (l i = 0; i <= allVis; i++) {
      l bitCount = count_bits(i);
      if (bitCount == halfBits) {
        l forward = inf, back = inf;
        for (l b = 1, bit = 1LL; b < n - 1; b++, bit <<= 1) {
          if ((bit & i) == 0) {
            l inv = ~i & allVis & ~bit;
            forward = min(forward, explore(i, 0, b) + explore(inv, b, n - 1));
            back = min(back, explore(i, n - 1, b) + explore(inv, b, 0));
          }
        }
        totalCost = min(totalCost, forward + back);
      }
    }
    printf("Case %d: %d\n", cases++, totalCost);
  }
}