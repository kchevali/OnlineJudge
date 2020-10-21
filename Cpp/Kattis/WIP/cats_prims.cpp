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

typedef tuple<double, l, l> T;
typedef vector<vector<T>> vT;

l mst(vT &edge, vector<ll> &result) {
  double weight = 0;
  vb visited(edge.size(), false);
  priority_queue<T> pq;

  visited[0] = true;
  for (auto x : edge[0]) pq.push(x);

  while (!pq.empty()) {
    auto t = pq.top();
    pq.pop();

    double w = -get<0>(t);
    l a = get<1>(t), b = get<2>(t);

    if (!visited[b]) {
      weight += w;
      result.PB((ll){a, b});  // store the MST
      visited[b] = true;
      for (auto x : edge[b]) {
        if (!visited[get<2>(x)]) pq.push(x);
      }
    }
  }
  return weight;  // return MST
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l t, i;
  cin >> t;
  fpp(i, 0, t) {
    l m, c, j;
    cin >> m >> c;
    l e = c * (c - 1) / 2;
    vvl adj = vvl(c, vl());
    fpp(j, 0, e) {}
  }
}