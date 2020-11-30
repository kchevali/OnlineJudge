
#include "../all.cpp"

const l N = 100 + 1;  // inf = 1e18;
l dis[N][N], dp[1 << (N - 2)][N], n;

l tsp(l vis, l a) {
  // if(dp[vis][a] != -1)return dp[vis][a];
  if (vis == 0) return dis[a][1];
  l cost = inf;
  for (l i = 2, bit = 1; i < n; i++, bit <<= 1) {
    if ((vis & bit) != 0) {
      cost = min(cost, dis[a][i] + tsp(vis & ~bit, i));
    }
  }
  return cost;
}

// int main() {

// }
