// #include <bits/stdc++.h>

// #define SHORT_INF 0x3f3f
// #define INT_INF 0x3f3f3f3f
// #define LL_INF 0x3f3f3f3f3f3f3f3f
// #define D_INF numeric_limits<double>::infinity()
// #define pb push_back
// #define mp make_pair
// #define l(x) x << 1
// #define r(x) x << 1 | 1
// #define mid(x, y) x + (y - x) / 2
// #define f first
// #define s second
// #define Fill(a, x) memset(a, x, sizeof(a))
// #define randi(a, b) rand() % (b - a + 1) + a
// #define db(x) cout << #x << " -> " << x << '\n'
// #define fpp(i, n) for (ll len = (ll)(n); i < len; ++i)
// #define fmm(i, n) for (ll len = (ll)i, i = (ll)n; i-- > len;)
// #define fpm(i, j, n) for (ll i = 0, j = (ll)n; j-- > 0; i++)

// using namespace std;

// typedef long long ll;
// typedef unsigned long long llu;
// typedef vector<string> vs;
// typedef vector<int> vi;
// typedef vector<ll> vll;
// typedef vector<double> vd;
// typedef pair<int, int> pii;
// typedef pair<float, float> pff;
// typedef pair<double, double> pdd;
// typedef pair<ll, ll> pll;
// typedef pair<llu, llu> pllu;
// typedef map<int, int> mii;
// typedef map<int, ll> mill;
// typedef map<ll, int> mlli;
// typedef unordered_map<int, int> umii;
// typedef unordered_map<int, ll> umill;
// typedef unordered_map<ll, int> umlli;

// class UF {
//  public:
//   vector<int> p, rank;

//   UF(int N) {
//     p = vector<int>(N);
//     rank = vector<int>(N, 0);
//     for (int i = 0; i < N; i++) p[i] = i;
//   }

//   int findSet(int i) {
//     if (p[i] == i)
//       return i;
//     else {
//       int ret = findSet(p[i]);
//       p[i] = ret;
//       return ret;
//     }
//   }

//   // return true if element i and j are in the same set, return false
//   otherwise bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

//   // union two sets that contain element i and j
//   void unionSet(int i, int j) {
//     if (!isSameSet(i, j)) {
//       int x = findSet(i), y = findSet(j);
//       // rank is used to keep the tree short
//       if (rank[x] > rank[y])
//         p[y] = x;
//       else {
//         p[x] = y;
//         if (rank[x] == rank[y]) rank[y] = rank[y] + 1;
//       }
//     }
//   }
// };

// int main() {
//   ios_base::sync_with_stdio(false);
//   cin.tie(NULL);
//   int n, m;
//   cin >> n >> m;
//   UF x = UF(n);
//   int i = 0;
//   fpp(i, m) {
//     char ch;
//     int a, b;
//     cin >> ch >> a >> b;
//     if (ch == '?')
//       cout << (x.isSameSet(a, b) ? "yes" : "no") << endl;
//     else
//       x.unionSet(a, b);
//   }
// }

#include <bits/stdc++.h>
#define C cout <<
#define _ << ' ' <<
#define E << "\n"
#define fpp(i, a, b) for (i = a; i < b; i++)
#define gc getchar_unlocked
using namespace std;
typedef long long l;
typedef vector<l> vl;

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

vl p, ranks;
l findSet(l i) { return p[i] == i ? i : (p[i] = findSet(p[i])); }

void unionSet(l x, l y) {
  if (ranks[x] > ranks[y])
    p[y] = x;
  else {
    p[x] = y;
    if (ranks[x] == ranks[y]) ranks[y]++;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m, i, a, b;
  char s;
  read(n);
  read(m);

  p = vl(n);
  ranks = vl(n, 0);
  iota(p.begin(), p.end(), 0);

  fpp(i, 0, m) {
    s = getchar();
    read(a);
    read(b);
    a = findSet(a);
    b = findSet(b);

    if (s == '?')
      C(a == b ? "yes" : "no") E;
    else
      unionSet(a, b);
  }
}