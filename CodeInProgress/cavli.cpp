#include <bits/stdc++.h>
using l = long long;
using o = double;
#define EPS 1e-6

struct Point {
  o x=0, y=0;
  Point() {}
  Point(o x, o y): x(x), y(y) {}

  bool operator==(const Point& other){
    return x == other.x && y == other.y;
  }
};

using Points = std::vector<Point>;

Point add(const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }
Point sub(const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }
Point scale(const Point& a, o c) { return Point(a.x * c, a.y * c); }

o dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
o cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
l cmp(o a, o b) { return fabs(a - b) < EPS ? 0 : (a > b ? 1 : -1); }
l sgn(l val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }
o sqrMag(const Point& a) { return dot(a, a); }
o distSq(const Point& a, const Point& b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
// left: postive // right: negative // colinear: 0
o ccw(const Point& p, const Point& a, const Point& b) { return cross(sub(a, p), sub(b, p)); }

Point firstPoint;
bool angleCmp(const Point& a, const Point& b) {
  auto deg = ccw(a, b, firstPoint);
  return deg == 0 ? (distSq(firstPoint, a) < distSq(firstPoint, b)) : deg > 0;
}
bool lexComp(const Point& a, const Point& b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }

l bottomLeftIndex(const Points &p, l n) {
  auto firstIndex = 0;
  for (auto i = 1; i < n; i++) {
    if (p[i].y < p[firstIndex].y || (p[i].y == p[firstIndex].y && p[i].x < p[firstIndex].x)) firstIndex = i;
  }
  return firstIndex;
}

// return the convex hull of a set of points
// required: firstPoint, ccw(),cross(),sub(),angleCmp
// Complexity: n log n
Points convexHull(Points &p) {
  auto n = p.size();
  std::swap(p[0], p[bottomLeftIndex(p, n)]);
  firstPoint = p[0];

  sort(p.begin() + 1, p.end(), angleCmp);
  auto q = Points();
  q.emplace_back(p[0]);
  // remove colinear points
  for (auto i = 2; i < n; i++)
    if (ccw(firstPoint, p[i - 1], p[i]) != 0) {
      q.emplace_back(p[i - 1]);
    }
  q.emplace_back(p[n - 1]);
  n = q.size();
  if (n <= 2) return q[0] == q[1] ? Points{q[0]} : q;

  auto hull = Points(2 * n);
  for (auto i = 0; i < 3; i++) hull[i] = q[i];
  auto h = 3;
  for (auto i = 3; i < n; i++) {
    while (ccw(hull[h - 2], hull[h - 1], q[i]) <= 0) h--;
    hull[h++] = q[i];
  }
  return Points(hull.begin(), hull.begin() + h);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);


}
