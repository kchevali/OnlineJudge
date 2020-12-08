#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef tuple<l, l, l> ll;

const l N = 1e5 + 10, inf = 0x3f3f3f3f3f3f3f3f;
l parent[N], depth[N], pairs[N], n = 0, m, totalPairs;
vector<l> adj[N];
// Complexity O(V+E)
const ll dfsRecursive(l a) {
  l total = 0, pairCount = totalPairs, bestPairTotal = 0, bestPairJoin = 0, joinA = 0, joinB = 0;
  for (auto b : adj[a]) {
    if (depth[b] == inf) {
      depth[b] = depth[a] + 1, parent[b] = a;
      auto &[childCount, best, join] = dfsRecursive(b);
      if (best > bestPairTotal) {
        bestPairTotal = best;
        bestPairJoin = join;
      }
      l count = childCount + 1;
      if (count > joinA) {
        joinB = joinA, joinA = count;
      } else if (count > joinB) {
        joinB = count;
      }

      total += count;
      pairCount -= count * (count - 1) / 2;
    }
  }
  // count back to parent
  l parentCount = n - total - 1;
  pairCount -= parentCount * (parentCount - 1) / 2;
  if (parentCount > joinA) {
    joinB = joinA, joinA = parentCount;
  } else if (parentCount > joinB) {
    joinB = parentCount;
  }

  if (pairCount > bestPairTotal) {
    bestPairTotal = pairCount;
    bestPairJoin = joinA * joinB;  //(joinA * (joinA - 1) + joinB * (joinB - 1)) / 2;
  }
  return {total, bestPairTotal, bestPairJoin};
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  scanf("%lld", &m);

  for (l i = 0; i < m; i++) {
    l a, b;
    scanf("%lld%lld", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
    n = max(n, max(a + 1, b + 1));
  }
  totalPairs = n * (n - 1) / 2;
  memset(depth, 0x3f, sizeof(l) * n);
  depth[0] = 0;
  auto &[_, mostPairs, mostJoined] = dfsRecursive(0);
  l solution = mostPairs - n + 1;
  cout << solution << " " << (solution - mostJoined) << "\n";
}