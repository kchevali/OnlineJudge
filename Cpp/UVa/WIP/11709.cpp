#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

void dfsSCC(l &a, vl *adj, stack<l> &st, l *onStack, l *ids, l *low, l &id,
            l &counter) {
  st.push(a);
  onStack[a] = true;
  ids[a] = low[a] = id++;
  for (auto &b : adj[a]) {
    if (ids[b] == -1) dfsSCC(b, adj, st, onStack, ids, low, id, counter);
    if (onStack[b]) low[a] = min(low[a], low[b]);
  }
  if (ids[a] == low[a]) {
    l c;
    do {
      c = st.top();
      st.pop();
      onStack[c] = false;
      low[c] = ids[a];
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
    map<string, l> mp;
    l index = 0;
    for (l i = 0; i < n; i++) {
      string a, b;
      cin >> a >> b;
      mp[a + b] = index++;
    }

    vl adj[n];
    l low[n];
    for (l i = 0; i < m; i++) {
      string a, b, c, d;
      cin >> a >> b >> c >> d;
      adj[mp[a + b]].emplace_back(mp[c + d]);
    }
    cout << SCC(adj, n, low) << "\n";
  }
}