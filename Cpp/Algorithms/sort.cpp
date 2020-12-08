#include "graph.cpp"

// Topological Sort(DAG): result in path
// l path[N];
// void dfsRecursive(l a, l& pathIndex);
// Complexity: O(V+E)
void topologicalSort(l n) {
  l pathIndex = n - 1;
  for (l i = 0; i < n; i++) {
    if (depth[i] == inf) {
      depth[i] = 0;
      parent[i] = i;
      dfsRecursive(i, pathIndex);
    }
  }
}

int main() {
  l n, m, i;
  cin >> n >> m;
  for (l i = 0; i < m; i++) {
    l a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  topologicalSort(n);
  for (l i = 0; i < n; i++) cout << path[i] << " ";
  cout << "\n";
  return 0;
}
/*
8 8
0 1
1 2
5 0
6 5
4 7
1 3
3 4
6 7




*/