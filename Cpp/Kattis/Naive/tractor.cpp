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
#define _ << "\t" <<
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l z, zz;
  I zz;
  fpp(z, 0, zz) {
    l w, h;
    I w >> h;
    ll a = {0, 0}, b = {0, 0};
    l tot = 0, factor = 1;

    while (a.F <= w && b.S <= h) {
      // DB(tot, factor, a.F, a.S, b.F, b.S);
      tot += a.S - b.S + 1;

      a.S += factor;
      b.F += factor;
      l dx = max(0LL, a.S - h);
      l dy = max(0LL, b.F - w);
      // DB(a.S, w, dx);
      if (dx > 0) {
        a.S = h;
        a.F += dx;
      }
      if (dy > 0) {
        b.F = w;
        b.S += dy;
      }

      factor *= 2;
    }
    C tot E;
  }
}