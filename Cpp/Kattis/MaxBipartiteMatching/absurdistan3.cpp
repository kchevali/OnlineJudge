#include <bits/stdc++.h>
#define I_INF 0x3f3f3f3f
#define L_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define PB emplace_back
#define MP make_pair
#define MT make_tuple
#define MID(x, y) x + (y - x) / 2
#define F first
#define S second
#define COUNT __builtin_popcountll
#define TRAIL __builtin_ffsll
#define LEAD __builtin_clzll
#define BIT(x, b) bitset<b>(x).to_string()
#define I cin >>
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
typedef set<l> sl;
typedef set<string> ss;
typedef map<l, l> ml;
typedef unordered_set<l> usl;
typedef unordered_map<l, l> uml;
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

l aug(l left, vvl &adj, vl &match, vb &vis) {
  if (vis[left]) return 0;
  vis[left] = true;

  for (auto right : adj[left]) {
    if (match[right] == -1 || aug(match[right], adj, match, vis) == 1) {
      match[right] = left;
      return 1;
    }
  }

  return 0;
}

vl getMatching(l v, l v_l, vvl adj) {
  l count = 0;
  vl match(v, -1);
  for (l i = v_l; i-- > 0;) {
    vb vis(v_l, false);
    count += aug(i, adj, match, vis);
  }
  return match;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, i;
  I n;
  vl edges = vl(n, 0);
  vvl adj = vvl(n, vl(2, 0));
  fpp(i, 0, n) {
    l a, b;
    I a >> b;
    adj[i][0] = a - 1;
    adj[i][1] = b - 1;
    l index = adj[i][0] + adj[i][1] * n;
    edges[i] = index;
  }
  vl m = getMatching(n, n, adj);
  fpp(i, 0, n) {
    l a = (edges[m[i]] % n) + 1;
    l b = (edges[m[i]] / n) + 1;
    if ((i + 1) == a)
      C a _ b E;
    else
      C b _ a E;
  }
}

/*
4
2 4
2 3
2 1
2 4


*/