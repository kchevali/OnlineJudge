#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << endl
#define _ << " " <<
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

typedef l d;  // weight type
typedef tuple<d, l, l> T;
typedef vector<vector<T>> vT;
typedef pair<l, l> ll;
typedef priority_queue<T, vector<T>, greater<T>> pq;  // max out
typedef vector<bool> vb;

vT adj;
vector<ll> result;
// result = vector<ll>();mst();
l mst() {
  d weight = 0;
  vb visited(adj.size(), false);
  pq q;

  visited[0] = true;
  for (auto x : adj[0]) q.push(x);

  while (!q.empty()) {
    auto t = q.top();
    q.pop();

    d w = get<0>(t);
    l a = get<1>(t), b = get<2>(t);

    if (!visited[b]) {
      weight += w;
      result.PB((ll){a, b});  // store the MST
      visited[b] = true;
      for (auto x : adj[b]) {
        if (!visited[get<2>(x)]) q.push(x);
      }
    }
  }
  return weight;  // return MST
}

l i, j, h, w;
d x;
void matrixToAdjTuple() {
  cin >> h;  //>>w;
  w = h;
  adj = vT(h, vector<T>());
  fpp(i, 0, h) {
    fpp(j, 0, w) {
      cin >> x;
      adj[i].PB(make_tuple(x, i, j));
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  matrixToAdjTuple();
  result = vector<ll>();
  mst();
  for (auto r : result) {
    l a, b;
    tie(a, b) = minmax(r.first, r.second);
    C(a + 1) _(b + 1) E;
  }
}
