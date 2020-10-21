#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
#define MID(x, y) x + (y - x) / 2
using namespace std;
typedef long long l;
typedef l o;

const double EPS = 1e-6;
typedef pair<o, o> oo;
typedef v(oo) voo;
#define xx first
#define yy second
typedef pair<l, l> ll;
typedef v(ll) vll;

oo sub(oo a, oo b) { return make_pair(a.xx - b.xx, a.yy - b.yy); }
o dot(oo a, oo b) { return a.xx * b.xx + a.yy * b.yy; }
o cross(oo a, oo b) { return a.xx * b.yy - a.yy * b.xx; }
o ccw(oo a, oo b, oo c) { return cross(sub(b, a), sub(c, a)); }
bool lexComp(oo a, oo b) {
  return a.yy < b.yy || (a.yy == b.yy && a.xx < b.xx);
}

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

vll readPts(l n) {
  vll pts(n);
  for (auto &p : pts) {
    read(p.xx);
    read(p.yy);
  }
  return pts;
}

l topRightIndex(voo &p, l n) {
  l i, index = 0;
  fpp(i, 1, n) {
    if (p[i].yy > p[index].yy ||
        (p[i].yy == p[index].yy && p[i].xx > p[index].xx))
      index = i;
  }
  return index;
}

//
void setCCW(voo &p, l n) {
  l i = 2, deg;
  while (i < n && (deg = ccw(p[i - 2], p[i - 1], p[i])) == 0) i++;
  if (deg < 0) reverse(p.begin(), p.end());
}

l sgn(l val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }

void rotateBottomToIndexZero(voo &p) {
  l n = p.size(), j = 0, i;
  fpp(i, 1, n) if (lexComp(p[i], p[j])) j = i;
  rotate(p.begin(), p.begin() + j, p.end());
}

l inSimplePolygon(oo point, voo poly) {
  l n = poly.size(), windingNumber = 0;
  for (int i = 0; i < n; ++i) {
    if (point == poly[i]) return 0;
    l j = (i + 1) % n;
    if (poly[i].yy == point.yy && poly[j].yy == point.yy) {
      if (min(poly[i].xx, poly[j].xx) <= point.xx &&
          point.xx <= max(poly[i].xx, poly[j].xx))
        return 0;
    } else {
      bool below = poly[i].yy < point.yy;
      if (below != (poly[j].yy < point.yy)) {
        auto orientation = ccw(point, poly[j], poly[i]);
        if (orientation == 0) return 0;
        if (below == (orientation > 0)) windingNumber += below ? 1 : -1;
      }
    }
  }
  return windingNumber == 0 ? 1 : -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m;
  read(n);
  while (n > 0) {
    vll pts = readPts(n);
    setCCW(pts, n);
    rotateBottomToIndexZero(pts);
    l top = topRightIndex(pts, n);
    read(m);
    vll qry = readPts(m);
    for (auto pt : qry) {
      l sol = inSimplePolygon(pt, pts);
      C(sol == 0 ? "on" : (sol == 1 ? "out" : "in")) E;
    }
    read(n);
  }
}
