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
#define dc(x) cout << fixed << setprecision(x) <<

const double EPS = 1e-6;
typedef pair<o, o> oo;
typedef v(oo) voo;
typedef v(voo) vvoo;
#define xx first
#define yy second

oo add(oo a, oo b) { return make_pair(a.xx + b.xx, a.yy + b.yy); }
oo sub(oo a, oo b) { return make_pair(a.xx - b.xx, a.yy - b.yy); }
o dot(oo a, oo b) { return a.xx * b.xx + a.yy * b.yy; }
o cross(oo a, oo b) { return a.xx * b.yy - a.yy * b.xx; }
oo scl(oo a, o b) { return make_pair(a.xx * b, a.yy * b); }
l cmp(o a, o b) { return abs(a - b) < EPS ? 0 : (a > b ? 1 : -1); }
l sgn(l val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }
o sqrLen(oo a) { return dot(a, a); }
o distSq(oo a, oo b) {
  return (a.xx - b.xx) * (a.xx - b.xx) + (a.yy - b.yy) * (a.yy - b.yy);
}
// left: postive // right: negative // colinear: 0
o ccw(oo p, oo a, oo b) { return cross(sub(a, p), sub(b, p)); }

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

typedef pair<l, l> ll;
typedef v(ll) vll;
vll readPts(l n) {
  vll pts(n);
  for (auto &p : pts) {
    read(p.xx);
    read(p.yy);
  }
  return pts;
}
double polygonArea(voo &list) {
  double area = 0;
  l i;
  fpp(i, 0, list.size()) area += cross(list[i], list[(i + 1) % list.size()]);
  return area / 2.0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, i = 0;
  read(n);
  while (n > 0) {
    vll pts = readPts(n);
    double a = polygonArea(pts);
    dc(1)(a > 0 ? "CCW" : "CW") _ fabs(a) E;
    read(n);
  }
}