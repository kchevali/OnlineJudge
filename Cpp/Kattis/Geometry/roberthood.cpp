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

const double pi = 2 * acos(0.0);

using namespace std;
typedef long long l;
typedef l o;
typedef v(l) vl;
typedef pair<l, l> ll;
typedef v(ll) vll;

const double EPS = 1e-8;
typedef pair<o, o> oo;
typedef v(oo) voo;
typedef v(bool) vb;
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

voo readPts(l n) {
  voo pts(n);
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
bool angleCmp(const oo a, const oo b) {
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
// required: firstPoint, ccw(),cross(),sub(),angleCmp

voo convexHull(voo &p) {
  l i, n = p.size();
  swap(p[0], p[smallestIndex(p, n)]);
  firstPoint = p[0];

  sort(p.begin() + 1, p.end(), angleCmp);
  voo q = voo();
  q.PB(p[0]);
  fpp(i, 2, n) if (ccw(firstPoint, p[i - 1], p[i]) != 0) { q.PB(p[i - 1]); }
  q.PB(p[n - 1]);
  n = q.size();
  if (n <= 2) return q[0] == q[1] ? voo{q[0]} : q;

  voo hull = voo(2 * n);
  fpp(i, 0, 3) hull[i] = q[i];
  l h = 3;
  fpp(i, 3, n) {
    while (ccw(hull[h - 2], hull[h - 1], q[i]) <= 0) h--;
    hull[h++] = q[i];
  }
  return voo(hull.begin(), hull.begin() + h);
}

double polygonDiameter(voo &p, l n) {
  if (n < 2)
    return 0;
  else if (n == 2)
    return sqrt(distSq(p[0], p[1]));  // distance between two points
  else {
    l i = n - 1, j = 0, k = 1;
    l res = 0;
    while (abs(cross(sub(p[j], p[i]), sub(p[k + 1], p[i]))) >
           abs(cross(sub(p[j], p[i]), sub(p[k], p[i])))) {
      k++;
    }
    i = 0, j = k;
    while (i <= k && j < n) {
      res = max(distSq(p[i], p[j]), res);
      while (j < n - 1 &&
             abs(cross(sub(p[i + 1], p[i]), sub(p[j + 1], p[i]))) >
                 abs(cross(sub(p[i + 1], p[i]), sub(p[j], p[i])))) {
        j++;
        res = max(distSq(p[i], p[j]), res);
      }
      i++;
    }
    return sqrt(res);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, i, j;
  read(n);
  voo pts = readPts(n);
  voo hull = convexHull(pts);
  printf("%.8f\n", polygonDiameter(hull, hull.size()));
}