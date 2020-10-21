#include <bits/stdc++.h>
using namespace std;
typedef long long l;

#define fpp(i, a, b) for (i = a; i < b; i++)
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
typedef double o;

#define dc(x) cout << fixed << setprecision(x) <<
#define MID(x, y) x + (y - x) / 2
#define iinf 100000000000LL

const double pi = 2 * acos(0.0);
const double EPS = 1e-6;

#define count __builtin_popcountll          // number of 'on' bits in long long
#define trail __builtin_ffsll               // index of first 'on' (1-64)
#define lead __builtin_clzll                // index of last  'on' (1-64)
#define bit(x, b) bitset<b>(x).to_string()  // prints x with b bits

#define xx first
#define yy second
// #define v(t) pair<t,t>

// TYPES

typedef v(l) vl;
typedef v(vl) vvl;
typedef pair<l, l> ll;
typedef v(ll) vll;
typedef v(vll) vvll;

typedef pair<bool, bool> bb;
typedef v(bool) vb;
typedef v(vb) vvb;
typedef v(bb) vbb;

typedef v(o) vo;
typedef v(vo) vvo;
typedef pair<o, o> oo;
typedef v(oo) voo;
typedef v(voo) vvoo;

typedef pair<o, l> ol;
typedef v(ol) vol;
typedef v(vol) vvol;

typedef unsigned long long ul;
typedef v(ul) vul;
typedef v(vul) vvul;
typedef pair<ul, ul> ull;
typedef v(ull) vull;

typedef v(double) vd;
typedef v(vd) vvd;
typedef pair<double, double> dd;
typedef v(dd) vdd;

typedef v(string) vs;
typedef v(vs) vvs;
typedef pair<string, string> ss;
typedef v(ss) vss;

// DATA STRUCTURES
typedef priority_queue<ll, vll, less<ll>> pql;     // min out
typedef priority_queue<ll, vll, greater<ll>> pqg;  // max out

typedef queue<l> ql;

//---------------------------------------------------------------DEBUGGING
#define con(x, a, b) \
  if (x < a || x >= b) cerr << "Out of Bounds: " << #x << endl;
#define arr(x)                  \
  C "[";                        \
  for (auto &y : x) C y << " "; \
  C "]" E;
#define db(args...)                          \
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

void tokenize() {
  string line, token;
  while (getline(cin, line)) {
    cout << line << "\n";
    stringstream ss(line);
    while (ss >> token) {
      cout << "Token: " << token << "\n";
    }
  }
}

//---------------------------------------------------------------Sorting
// sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
//   return a.first == b.first ? a.second > b.second : a.first < b.first;
// });

void read(l &x) {
  l c = gc();
  x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc())
    ;
  if (c == '-') {
    neg = 1;
    c = gc();
  }
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
  if (neg) x = -x;
}

const l N = 510;
vll adj[N];
l dis[N];
l r[N];
bool vis[N];
bool isRepair[N];

struct edge {
  l b, w, rem;
  bool operator<(edge a) const { return w > a.w; }
};

edge make_e(l b, l w, l rem) {
  edge start;
  start.b = b;
  start.w = w;
  start.rem = rem;
  return start;
}

l n, m, t, d;

void dijkstra(l source, l n) {
  for (l i = 0; i < n; i++) {
    dis[i] = iinf;
    vis[i] = 0;
    r[i] = 0;
  }
  priority_queue<edge> pq;  // w, node

  dis[source] = 0;

  pq.push(make_e(source, 0, d));
  while (!pq.empty()) {
    auto curr = pq.top();
    pq.pop();
    l a = curr.b, W = curr.w;
    l rem = (isRepair[a] ? d : curr.rem);
    // cout << "POP: " << a << " size: " << adj[a].size() << "\n";
    // if (vis[a]) continue;
    vis[a] = true;
    for (l i = 0; i < adj[a].size(); i++) {
      l b = adj[a][i].second, w = adj[a][i].first;
      // cout << "\n";
      // db(a, b, W, w, rem);
      if ((W + w < dis[b] || rem - w > r[b]) && rem >= w) {
        dis[b] = min(dis[b], w + W);
        r[b] = max(r[b], rem - w);
        // cout << "ADDING TO QUEUE:" << b << "\n";
        pq.push(make_e(b, w + W, rem - w));
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> t >> d;
  for (l i = 0; i < n; i++) {
    isRepair[i] = false;
    adj[i] = vll();
  }
  for (l i = 0; i < t; i++) {
    l a;
    cin >> a;
    a--;
    isRepair[a] = true;
  }
  for (l i = 0; i < m; i++) {
    l a, b, w;
    cin >> a >> b >> w;
    a--;
    b--;
    adj[a].emplace_back(make_pair(w, b));
    adj[b].emplace_back(make_pair(w, a));
  }
  dijkstra(0, n);
  cout << (dis[n - 1] == iinf ? "stuck" : to_string(dis[n - 1])) << "\n";
}
/*
2 1 0 1
1 2 1

5 5 1 5
2
1 2 6
2 3 1
3 5 1
1 4 2
4 5 4

4 4 1 10
2
1 2 10
2 3 1
1 3 2
3 4 9



*/