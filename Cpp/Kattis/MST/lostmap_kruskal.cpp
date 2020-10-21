#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

typedef l d;
typedef tuple<d, l, l> T;
typedef vector<T> vT;
typedef vector<vT> vvT;

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

vT adj;
l h, w;

void arrToAdjTuple() {
  read(h);  //>>w;
  w = h;
  adj = vT();
  l i, j;
  d x;
  fpp(i, 0, h) {
    fpp(j, 0, w) {
      read(x);
      if (i < j) adj.PB(make_tuple(x, i, j));
    }
  }
}

vl p, ranks;
l findSet(l i) { return p[i] == i ? i : p[i] = findSet(p[i]); }
// return true if element i and j are in the same set, return false otherwise
bool isSameSet(l i, l j) { return findSet(i) == findSet(j); }
// union two sets that contain element i and j
void unionSet(l i, l j) {
  l x = findSet(i), y = findSet(j);
  if (x == y) return;
  // ranks is used to keep the tree short
  if (ranks[x] > ranks[y])
    p[y] = x;
  else {
    p[x] = y;
    if (ranks[x] == ranks[y]) ranks[y]++;
  }
}

d weight;
vT kruskal_mst(vT &v, l n) {
  sort(v.begin(), v.end());
  weight = 0;
  vT result = vT();
  for (T e : v) {
    if (!isSameSet(get<1>(e), get<2>(e))) {
      result.PB(e);
      unionSet(get<1>(e), get<2>(e));
      weight += get<0>(e);
    }
  }
  return result;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  arrToAdjTuple();
  p = vl(h, 0);
  ranks = vl(h, 0);
  iota(p.begin(), p.end(), 0);
  vT result = kruskal_mst(adj, h);
  for (T e : result) {
    C(get<1>(e) + 1) _(get<2>(e) + 1) E;
  }
}
