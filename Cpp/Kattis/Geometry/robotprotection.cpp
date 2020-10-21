#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
#define dc(x) cout << fixed << setprecision(x) <<

using namespace std;
typedef long long l;
typedef l o;
typedef pair<l, l> ll;
typedef v(ll) vll;

const double EPS = 1e-6;
typedef pair<o, o> oo;
typedef v(oo) voo;
#define xx first
#define yy second

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
  for (int i = 0; i < n; i++) {
    read(pts[i].xx);
    read(pts[i].yy);
  }
  return pts;
}

oo sub(oo a, oo b) { return make_pair(a.xx - b.xx, a.yy - b.yy); }
o dot(oo a, oo b) { return a.xx * b.xx + a.yy * b.yy; }
o cross(oo a, oo b) { return a.xx * b.yy - a.yy * b.xx; }
l cmp(o a, o b) { return abs(a - b) < EPS ? 0 : (a > b ? 1 : -1); }
o distSq(oo a, oo b) {
  return (a.xx - b.xx) * (a.xx - b.xx) + (a.yy - b.yy) * (a.yy - b.yy);
}
// left: postive // right: negative // colinear: 0
o ccw(oo a, oo b, oo c) { return cross(sub(b, a), sub(c, a)); }
oo firstPoint;
bool cmpAngleToFirstPoint(const oo a, const oo b) {
  l deg = ccw(a, b, firstPoint);
  return deg == 0 ? (distSq(firstPoint, a) < distSq(firstPoint, b)) : deg > 0;
}

l smallestIndex(voo &p, l n) {
  l i, firstIndex = 0;
  fpp(i, 1, n) {
    if (p[i].yy < p[firstIndex].yy ||
        (p[i].yy == p[firstIndex].yy && p[i].xx < p[firstIndex].xx))
      firstIndex = i;
  }
  return firstIndex;
}

// return the convex hull of a set of points
// required: firstPoint, ccw(),cross(),sub(),cmpAngleToFirstPoint

voo convexHull(voo &p) {
  l i, n = p.size();
  swap(p[0], p[smallestIndex(p, n)]);
  firstPoint = p[0];

  sort(p.begin() + 1, p.end(), cmpAngleToFirstPoint);
  fpp(i, 2, n) {
    if (ccw(firstPoint, p[i - 1], p[i]) == 0) {
      p.erase(p.begin() + (--i));
      n--;
    }
  }
  if (n <= 2) return p[0] == p[1] ? voo{p[0]} : p;

  voo hull = voo(2 * n);
  fpp(i, 0, 3) hull[i] = p[i];
  l h = 3;
  fpp(i, 3, n) {
    while (ccw(hull[h - 2], hull[h - 1], p[i]) <= 0) h--;
    hull[h++] = p[i];
  }
  return voo(hull.begin(), hull.begin() + h);
}

double polygonArea(voo &list) {
  double area = 0;
  l i;
  fpp(i, 0, list.size()) area += cross(list[i], list[(i + 1) % list.size()]);
  return abs(area) / 2.0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n;
  read(n);
  while (n > 0) {
    voo pts = readPts(n);

    voo hull = convexHull(pts);
    dc(1) polygonArea(hull) E;
    read(n);
  }
}
