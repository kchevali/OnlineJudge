#include <bits/stdc++.h>
using namespace std;
typedef int l;

const l N = 1e5 + 10;  //, inf = 0x3f3f3f3f3f3f3f3f;
l diameters[N];
vector<l> adj[N];
unordered_map<l, l> depth;
bool vis[N];
// Complexity O(V+E)
void dfs(l src, l& maxDistIndex) {
  depth = unordered_map<l, l>();
  depth[src] = 0;
  stack<l> st;
  st.push(src);
  while (!st.empty()) {
    l a = st.top();
    st.pop();
    for (auto& b : adj[a]) {
      if (depth.find(b) == depth.end()) {
        vis[b] = true;
        if ((depth[b] = depth[a] + 1) > depth[maxDistIndex]) maxDistIndex = b;  // get tree diameter
        st.push(b);
      }
    }
  }
}

l get_tree_diameter(l src) {
  l maxDistIndex = src;
  dfs(src, maxDistIndex);
  dfs(maxDistIndex, maxDistIndex);
  return depth[maxDistIndex];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m;
  cin >> n >> m;

  for (l i = 0; i < m; i++) {
    l a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  memset(vis, 0, sizeof(vis));

  l length = 0;
  for (l i = 0; i < n; i++) {
    if (!vis[i]) {
      vis[i] = true;
      diameters[length++] = get_tree_diameter(i);
    }
  }
  sort(diameters, diameters + length);
  while (length > 1) {
    l &a = diameters[length - 2], &b = diameters[--length];
    a = max(b, (a >> 1) + (b >> 1) + (a & 1) + (b & 1) + 1);  // change
  }
  cout << diameters[0] << "\n";
}
