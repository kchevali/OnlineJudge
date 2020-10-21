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
typedef v(voo) vvoo;
typedef pair<l, l> ll;
typedef v(ll) vll;
typedef v(bool) vb;
#define xx first
#define yy second
#define dc(x) cout << fixed << setprecision(x) <<

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

// return true if point P lies on line AB
bool inSegment(oo a, oo b, oo p) {
  if (cmp(ccw(a, b, p), 0) != 0) return false;
  oo tmp = sub(b, a);
  o dotProduct = dot(sub(p, a), tmp);
  return !(cmp(dotProduct, 0) < 0 || cmp(dotProduct, dot(tmp, tmp)) > 0);
}

l inTriangle(oo a, oo b, oo c, oo p) {
  if (inSegment(a, b, p) || inSegment(a, c, p) || inSegment(b, c, p)) return 0;
  return cmp(abs(ccw(a, b, c)),
             abs(ccw(p, a, b)) + abs(ccw(p, b, c)) + abs(ccw(p, c, a))) == 0
             ? -1
             : 1;
}

// Adds a point p to given convex hull O(n)
void addPointHull(voo &hull, oo p) {
  l n = hull.size();
  voo ret;
  // point having minimum distance from the point p
  l h = 0, i, j;
  fpp(i, 1, n) if (distSq(p, hull[i]) < distSq(p, hull[h])) h = i;

  // Find the tangents
  l up = h, low = h;
  while (ccw(p, hull[up], hull[(up + 1) % n]) >= 0) up = (up + 1) % n;
  while (ccw(p, hull[low], hull[(n + low - 1) % n]) <= 0)
    low = (n + low - 1) % n;

  // making the final hull by traversing points
  // from up to low of given convex hull.
  l curr = up;
  ret.PB(hull[curr]);
  while (curr != low) ret.PB(hull[curr = (curr + 1) % n]);

  // Modify the original vector
  ret.PB(p);
  hull.clear();
  fpp(i, 0, ret.size()) hull.PB(ret[i]);
}

double polygonArea(voo &list) {
  double area = 0;
  l i;
  fpp(i, 0, list.size()) area += cross(list[i], list[(i + 1) % list.size()]);
  return fabs(area) / 2.0;
}
const l N = 300000;
map<l, l> mp;

l ind(oo pt) { return mp[pt.xx + pt.yy * N]; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, i, j, k;
  cin >> n;
  voo pts(n);
  for (auto &p : pts) cin >> p.xx >> p.yy;
  string s;
  cin >> s;

  fpp(i, 0, n) mp[pts[i].xx + pts[i].yy * N] = i;
  //   fpp(i, 0, n) C "GOT:" _ pts[i].xx _ pts[i].yy _ ind(pts[i]) E;

  voo xs = voo(n), ys = voo(n);
  vb removed = vb(n, false);

  l xi = 0, xj = n - 1, yi = 0, yj = n - 1;

  fpp(i, 0, n) {
    xs[i] = make_pair(pts[i].xx, pts[i].yy);
    ys[i] = make_pair(pts[i].xx, pts[i].yy);
  }
  sort(xs.begin(), xs.end(),
       [](const oo &a, const oo &b) { return a.xx < b.xx; });
  sort(ys.begin(), ys.end(),
       [](const oo &a, const oo &b) { return a.yy < b.yy; });

  //   C "X:" E;
  //   for (auto pt : xs) C pt.xx _ pt.yy E;

  //   C "Y:" E;
  //   for (auto pt : ys) C pt.xx _ pt.yy E;

  voo order = voo(n - 2);
  l index = n - 3;
  for (char ch : s) {
    switch (ch) {
      case 'L':
        while (removed[ind(xs[xi])]) xi++;
        removed[ind(xs[xi])] = true;
        order[index--] = xs[xi++];
        break;
      case 'R':
        while (removed[ind(xs[xj])]) xj--;
        removed[ind(xs[xj])] = true;
        order[index--] = xs[xj--];
        break;
      case 'U':
        while (removed[ind(ys[yj])]) yj--;
        removed[ind(ys[yj])] = true;
        order[index--] = ys[yj--];
        break;
      case 'D':
        while (removed[ind(ys[yi])]) yi++;
        removed[ind(ys[yi])] = true;
        order[index--] = ys[yi++];
    }
  }
  //   C "PTS:" E;
  //   for (auto pt : order) C pt.xx _ pt.yy E;
  v(double) area = v(double)(n - 2);
  voo hull = voo();
  fpp(i, 0, n) if (removed[i] == 0) {
    hull.PB(pts[i]);
    // C "UNREMOVED:" _ i E;
  }
  //   C "\nHULL:" E;
  //   for (auto pt : hull) C pt.xx _ pt.yy E;
  //   if (ccw(hull[0], hull[1], hull[2]) < 0) swap(hull[0], hull[1]);

  fpp(i, 0, n - 2) {
    // C "\nBEFORE:" E;
    // for (auto pt : hull) C pt.xx _ pt.yy E;
    // C "Area:" _ polygonArea(hull) E;

    // C "Trying To Insert:" _ order[i].xx _ order[i].yy E;
    addPointHull(hull, order[i]);
    // C "AFTER:" E;
    // for (auto pt : hull) C pt.xx _ pt.yy E;
    // C "Area:" _ polygonArea(hull) E;
    area[i] = polygonArea(hull);
  }
  fmm(i, 0, n - 2) dc(1) area[i] E;
}

/*
5
1 4
2 2
4 1
3 5
5 3
RRR


 */