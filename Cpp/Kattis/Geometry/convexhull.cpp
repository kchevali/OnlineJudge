#include <bits/stdc++.h>
using l = long long;
using o = l;
#define EPS 1e-6

#define gc getchar_unlocked
void readInt(l &x) {
  l c = gc();
  x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc());
  if (c == '-') {
    neg = 1;
    c = gc();
  }
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
  if (neg) x = -x;
}

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

l bottomLeftIndex(const Points &p, l n) {
  auto firstIndex = 0;
  for (auto i = 1; i < n; i++) {
    if (p[i].y < p[firstIndex].y || (p[i].y == p[firstIndex].y && p[i].x < p[firstIndex].x)) firstIndex = i;
  }
  return firstIndex;
}

Point firstPoint;
bool angleCmp(const Point& a, const Point& b) {
  auto deg = ccw(a, b, firstPoint);
  return deg == 0 ? (distSq(firstPoint, a) < distSq(firstPoint, b)) : deg > 0;
}


// return the convex hull of a set of points
// required: firstPoint, ccw(),cross(),sub(),angleCmp
// out - required buffer size of 2*p.size()
// Complexity: n log n
void convexHull(Points& p, l n, Points& q, Points& out, l& outLength) {
    std::swap(p[0], p[bottomLeftIndex(p, n)]);
    firstPoint = p[0];

    sort(p.begin() + 1, p.begin() + n, angleCmp);
    auto qi = 0;
    q[qi++] = p[0];
    // remove colinear points
    for (auto i = 2; i < n; i++)
        if (ccw(firstPoint, p[i - 1], p[i]) != 0) {
            q[qi++] = p[i - 1];
        }
    q[qi++] = p[n - 1];
    n = qi;
    if (n <= 2){
        out[0] = q[0], out[1] = q[1];
        outLength = (n == 2 && q[0] == q[1]) ? 1 : n;
        return;
    }

    outLength = 3;
    for (auto i = 0; i < outLength; i++) out[i] = q[i];
    for (auto i = outLength; i < n; i++) {
        while (ccw(out[outLength - 2], out[outLength - 1], q[i]) <= 0) outLength--;
        out[outLength++] = q[i];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l N = 10000;
    Points points(N);
    Points hull(2*N);
    Points buffer(N);
    l hullLength = 0;

    l n;
    readInt(n);
    while(n > 0){
        for(l i = 0; i < n; i++){
            readInt(points[i].x), readInt(points[i].y);
        }
        firstPoint = points[0];
        convexHull(points, n, buffer, hull, hullLength);

        std::printf("%lld\n", hullLength);
        for(l i = 0; i < hullLength; i++){
            std::printf("%lld %lld\n", hull[i].x, hull[i].y);
        }
        readInt(n);
    }
}