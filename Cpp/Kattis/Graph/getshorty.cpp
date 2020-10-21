#include <bits/stdc++.h>
using namespace std;
typedef long long l;
#define dc(x) cout << fixed << setprecision(x) <<
typedef pair<double, l> dl;
typedef priority_queue<dl, vector<dl>, less<dl>> pql;  // min out

double dijkstra(l src, vector<vector<dl>> &adj)  // start, end, adj[a][i], w[a][b]
{
  vector<double> dis(adj.size(), 0);
  pql q;  // element {current height, current node number}
  q.push({dis[src] = 1, src});
  while (!q.empty()) {
    dl p = q.top();  // pq.poll()
    q.pop();

    l a = p.second;  // current node number
    if (a == adj.size() - 1) return dis[adj.size() - 1];
    for (dl pp : adj[a]) {           // go to all adj nodes
      l b = pp.second;               // next node number
      double d = dis[a] * pp.first;  //(current height at a) * (fraction of the next node)
      // cout << "FROM: " << a << " TO " << b << " Height: " << d << "\n";
      if (d > dis[b]) {
        q.push({dis[b] = d, b});  //{current height at node b, the node number b}
      }
    }
  }
  return dis[adj.size() - 1];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m;
  while (true) {
    cin >> n >> m;
    if (n + m == 0) break;
    vector<vector<dl>> adj(n);
    for (int i = 0; i < m; i++) {
      l a, b;
      double w;
      cin >> a >> b >> w;
      adj[a].push_back(make_pair(w, b));  //(fraction , node number)
      adj[b].push_back(make_pair(w, a));
    }
    dc(4)((dijkstra(0, adj))) << "\n";
  }
}