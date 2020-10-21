#include "graph.cpp"

vl topologicalSort(vvl& adj) {
  vl endTimes = dfs(adj), result = vl(adj.size(), 0);
  for (l i = 0; i < result.size(); i++) result[endTimes[i]] = i;
  return result;
}

int main() {
  l n, m, i;
  cin >> n >> m;
  vvl adj(n);
  for (l i = 0; i < m; i++) {
    l a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  for (auto& a : topologicalSort(adj)) cout << a << " ";
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