#include <bits/stdc++.h>
using l = long long;
using o = double;
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
  double angle = 0;
  Point() {}
  Point(o x, o y): x(x), y(y) {}

  bool operator==(const Point& other){
    return x == other.x && y == other.y;
  }
};

using Points = std::vector<Point>;

Point sub(const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }
o cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
o distSq(const Point& a, const Point& b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
// left: postive // right: negative // colinear: 0
o ccw(const Point& p, const Point& a, const Point& b) { return cross(sub(a, p), sub(b, p)); }


Point centerPoint;
bool angleCmp(const Point& a, const Point& b) {
  return a.angle < b.angle;
}

double getAngle(const Point& a, const Point& b) {
    return atan2(b.y - a.y, b.x - a.x);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l n;
    std::scanf("%lld", &n);
    Points points(n);

    l idx = 0;
    char ch = 0;
    for(l i = 0; i < n; i++){
        l x, y;
        std::scanf("%lld %lld %c", &x, &y, &ch);
        points[idx].x = x;
        points[idx].y = y;
        if(ch == 'Y'){
            centerPoint.x += points[idx].x;
            centerPoint.y += points[idx].y;
            idx++;
        }
    }
    centerPoint.x /= idx;
    centerPoint.y /= idx;

    for(l i = 0; i < idx; i++){
        points[i].angle = getAngle(centerPoint, points[i]);
    }

    sort(points.begin(), points.begin() + idx, angleCmp);

    l minX = 0;
    for(l i = 1; i < idx; i++){
        if(points[i].x < points[minX].x || (points[i].x == points[minX].x && points[i].y < points[minX].y)){
            minX = i;
        }
    }

    std::printf("%lld\n", idx);
    for(l i = 0; i < idx; i++){
        const auto& pt = points[(i + minX) % idx];
        std::printf("%lld %lld\n", (l)pt.x, (l)pt.y);
    }
}
