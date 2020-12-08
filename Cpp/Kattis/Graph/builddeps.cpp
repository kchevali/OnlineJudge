#include <bits/stdc++.h>
using namespace std;
typedef long long l;

const l N = 100000 + 10, inf = 0x3f3f3f3f3f3f3f3f;
l parent[N], depth[N];
string f[N];
vector<l> adj[N];

l path[N];
// Complexity: O(V+E)
void dfsRecursive(l a, l& pathIndex) {
  for (l b : adj[a]) {
    if (depth[b] == inf) {
      depth[b] = depth[a] + 1;
      parent[b] = a;
      dfsRecursive(b, pathIndex);
    }
  }
  path[pathIndex--] = a;  // topological sort
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  unordered_map<string, l> files;
  memset(depth, 0x3f, sizeof(depth));

  l n, strIndex = 0;
  cin >> n;
  cin.ignore();
  for (l i = 0; i < n; i++) {
    string line, str;
    getline(cin, line);
    stringstream ss(line);
    bool first = true;
    l a;
    while (ss >> str) {
      if (first) str.pop_back();
      l b;
      if (files.find(str) == files.end()) {
        f[strIndex] = str;
        b = files[str] = strIndex++;
      } else {
        b = files[str];
      }
      if (first) {
        a = b;
        first = false;
      } else {
        adj[b].emplace_back(a);
      }
    }
  }
  string x;
  cin >> x;
  l src = files[x];
  l pathIndex = n - 1;

  depth[src] = 0;
  parent[src] = src;
  dfsRecursive(src, pathIndex);

  for (l i = pathIndex + 1; i < n; i++) {
    l num = path[i];
    if (depth[num] != inf) {
      cout << f[num] << "\n";
    }
  }
}
