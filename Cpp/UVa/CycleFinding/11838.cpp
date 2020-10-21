#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

// Tarjan's Strongly Connected Component
// Cycle detection

// supporting
void dfsSCC(l &a, vl *adj, stack<l> &st, l *onStack, l *ids, l *low, l &id,
            l &counter) {
  st.push(a);
  // cout << "\nAdding: " << (a + 1) << "\n";
  onStack[a] = true;
  ids[a] = low[a] = id++;
  // cout << "LOW of " << (a + 1) << " is " << ids[a] << "\n";
  for (auto &b : adj[a]) {
    // cout << "Node: " << (a + 1) << " ADJ: " << (b + 1) << "\n";
    if (ids[b] == -1) dfsSCC(b, adj, st, onStack, ids, low, id, counter);
    if (onStack[b]) low[a] = min(low[a], low[b]);
    // cout << "LOW of " << (a + 1) << " is " << low[a] << "(DFS)\n";
  }
  if (ids[a] == low[a]) {
    l c;
    do {
      c = st.top();
      st.pop();
      // cout << "Popping: " << (c + 1) << "\n";
      onStack[c] = false;
      low[c] = ids[a];
      // cout << "LOW of " << (c + 1) << " is " << low[c] << "(C)\n";
    } while (c != a);
    counter++;
  }
}
// main - low -> uninit array[n]
l SCC(vl *adj, l n, l *low) {
  l id = 0, counter = 0;
  l ids[n], onStack[n];
  stack<l> st;
  for (l i = 0; i < n; i++) {
    ids[i] = -1;
    onStack[i] = false;
  }
  for (l i = 0; i < n; i++)
    if (ids[i] == -1) dfsSCC(i, adj, st, onStack, ids, low, id, counter);
  return counter;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (true) {
    l n, m;
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    vl adj[n];
    for (l i = 0; i < m; i++) {
      l a, b, p;
      cin >> a >> b >> p;
      a--;
      b--;
      adj[a].emplace_back(b);
      if (p == 2) adj[b].emplace_back(a);
    }
    l low[n];
    l ans = SCC(adj, n, low);
    cout << (ans == 1 ? 1 : 0) << "\n";
    // cout << "LOWS: ";
    // for (l i = 0; i < n; i++) cout << low[i] << " ";
    // cout << "\n";
    // cout << "Counter: " << (ans == 1 ? 1 : 0) << "\n";
  }
}

/*
4 4
1 2 1
2 3 1
3 1 1
2 4 2

5 5
1 3 2
2 1 1
1 4 1
4 5 1
5 2 1

*/
