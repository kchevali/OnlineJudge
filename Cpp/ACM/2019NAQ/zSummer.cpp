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
#define iinf 0x3f3f3f3fLL

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  l n = s.length();
  l mx = 0;
  vl found(0);

  for (l i = 0; i < n; i++) {
    found = vl(26, false);
    for (l j = i + 1; j < n; j++) {
      if (s[i] == s[j]) break;
      l index = s[j] - 'a';
      mx += found[index] == 0;
      found[index] = 1;
    }
  }
  cout << mx << "\n";
}
