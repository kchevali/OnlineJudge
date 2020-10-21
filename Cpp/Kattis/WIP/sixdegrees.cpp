#include <bits/stdc++.h>
#define I_INF 0x3f3f3f3f
#define L_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define PB emplace_back
#define MID(x, y) x + (y - x) / 2
#define X first
#define Y second
#define COUNT __builtin_popcountll
#define TRAIL __builtin_ffsll
#define LEAD __builtin_clzll
#define BIT(x, b) bitset<b>(x).to_string()
#define C cout <<
#define DC(x) cout << fixed << setprecision(x) <<
#define E << endl
#define _ << " " <<
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define CON(x, a, b) \
  if (x < a || x >= b) cerr << "Out of Bounds: " << #x << endl;
#define ARR(x)                  \
  C "[";                        \
  for (auto &y : x) C y << " "; \
  C "]" E;
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef pair<l, l> ll;
typedef pair<double, double> dd;
typedef queue<l> ql;
typedef priority_queue<ll, vector<ll>, greater<ll>> pql;
#define DB(args...)                          \
  {                                          \
    string _s = #args;                       \
    replace(_s.begin(), _s.end(), ',', ' '); \
    stringstream _ss(_s);                    \
    istream_iterator<string> _it(_ss);       \
    err(_it, args);                          \
    cerr E;                                  \
  }
void err(istream_iterator<string> it) {}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " = " << a << "   ";
  err(++it, args...);
}
const double pi = 2 * acos(0.0);

// BFS: Unweighted - find path
vl bfs(l a0, vvl &adj) {
  vl prev(adj.size(), -1);
  vl d(adj.size(), -1);
  ql q;
  q.push(prev[a0] = a0);
  d[a0] = 0;
  while (!q.empty()) {
    l a = q.front();
    q.pop();
    for (l b : adj[a]) {
      if (prev[b] == -1) {
        q.push(b);
        prev[b] = a;
        d[b] = d[a] + 1;
      }
    }
  }
  return d;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l zz, zzz;
  cin >> zzz;
  fpp(zz, 0, zzz) {
    l m, i, j, n = 0;
    cin >> m;
    auto mp = map<string, l>();
    auto adj = vvl();
    fpp(i, 0, m) {
      string a, b;
      cin >> a >> b;
      if (mp.find(a) == mp.end()) {
        mp[a] = n++;
        adj.PB();
      }
      if (mp.find(b) == mp.end()) {
        mp[b] = n++;
        adj.PB();
      }
      l al = mp[a], bl = mp[b];
      adj[al].PB(bl);
      adj[bl].PB(al);
    }
    vb big = vb(n, false);
    l bigCount = 0;
    fpp(i, 0, n) {
      vl d = bfs(i, adj);
      fpp(j, 0, n) {
        if (d[j] > 6 && !big[j]) {
          big[j] = true;
          bigCount++;
        }
      }
    }

    C((bigCount * 100 / n) > 5 ? "NO" : "YES") E;
    //===
  }
}
/*
2
6
132.229.123.1 132.229.123.2
132.229.123.2 132.229.123.3
132.229.123.3 132.229.123.4
132.229.123.4 132.229.123.5
132.229.123.5 132.229.123.6
132.229.123.6 xxxxx
7
a b
b c
c d
d e
e f
f g
g h

*/