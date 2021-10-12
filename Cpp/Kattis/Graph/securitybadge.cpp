#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef tuple<l,l,l> edge; // node, lower, upper

// BFS: Unweighted - find path from one source
const l N = 1e3 + 10;
bool vis[N];
vector<edge> adj[N];
// Complexity O(V+E)
bool bfs(l src, l dest, l id) {
  if(src == dest)return true;
  queue<l> q;
  q.push(src);
  vis[src] = true;
  while (!q.empty()) {
    l a = q.front();
    q.pop();
    for (auto [b, lower, upper] : adj[a]) {
      if (!vis[b] && id >= lower && id <= upper) {
        if(dest == b)return true;
        vis[b] = true, q.push(b);
      }
    }
  }
  return false;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m, b;
  cin >> n >> m >> b;
  b--;

  l src, dest;
  cin >> src >> dest;
  src--, dest--;

  unordered_set<l> setIds;
  setIds.insert(0);
  setIds.insert(b);

  for(l i = 0; i < m; i++){
    l nodeA, nodeB, badgeA, badgeB;
    cin >> nodeA >> nodeB >> badgeA >> badgeB;
    nodeA--, nodeB--, badgeA--, badgeB--;
    adj[nodeA].push_back({nodeB, badgeA, badgeB});
    setIds.insert(badgeA);
    setIds.insert(badgeB);
  }
  vector<l> ids(setIds.begin(), setIds.end());
  sort(ids.begin(), ids.end());

  l idCount = ids.size();
  unordered_map<l,l> idIndex;
  for(l i = 0; i < idCount; i++) idIndex[ids[i]] = i;

  for(l i = 0; i < n; i++){
    for(auto &[node, badgeA, badgeB] : adj[i]){
      badgeA = 2*idIndex[badgeA];
      badgeB = 2*idIndex[badgeB];
    }
  }

  l total = 0;
  for(l i = 1; i < 2*idCount; i++){
    memset(vis,0,sizeof(bool)*n);
    bool result = bfs(src, dest, i-1);
    l offset = 1 - i%2;
    l numA = ids[ i / 2] - offset, numB = ids[i / 2 - offset] + offset;
    if(numB > numA)continue;
    total += result * (numA - numB + 1);
  }

  cout << total << "\n";
}