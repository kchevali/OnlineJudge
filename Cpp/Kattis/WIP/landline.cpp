#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
using namespace std;
typedef long long l;
typedef l o;
typedef v(bool) vb;

typedef tuple<o, l, l> T;
typedef vector<T> vT;
typedef vector<vT> vvT;
typedef pair<l, l> ll;
typedef vector<bool> vb;
typedef priority_queue<T, vector<T>, greater<T>> pq;  // max out

l n;
vvT adj;
vb insecure = vb(n, false);
vb visited;

l prim_mst() {
  o weight = 0;
  visited = vb(adj.size(), false);
  pq q;

  l root = 0;
  while (insecure[root]) root++;

  visited[root] = true;
  for (auto x : adj[root]) {
    q.push(x);
  }

  while (!q.empty()) {
    auto t = q.top();
    q.pop();

    o w = get<0>(t);
    l a = get<1>(t), b = get<2>(t);

    if (insecure[a]) continue;

    if (!visited[b]) {
      weight += w;
      visited[b] = true;
      for (auto x : adj[b]) {
        if (!visited[get<2>(x)]) {
          q.push(x);
        }
      }
    }
  }
  return weight;  // return MST
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l m, p, i, j;

  cin >> n >> m >> p;
  insecure = vb(n, false);
  adj = vvT(n, vT());
  fpp(i, 0, p) {
    cin >> j;
    insecure[j - 1] = true;
  }
  fpp(i, 0, m) {
    l a, b, w;
    cin >> a >> b >> w;
    a--;
    b--;
    if (!insecure[a] || !insecure[b]) {
      adj[a].PB(make_tuple(w, a, b));
      adj[b].PB(make_tuple(w, b, a));
    }
  }
  fpp(i, 0, n) {
    if (adj[i].size() == 0) {
      C "impossible" E;
      return 0;
    }
  }
  l cost = prim_mst();
  fpp(i, 0, n) if (!visited[i]) {
    C "impossible" E;
    return 0;
  }

  C cost E;
}
