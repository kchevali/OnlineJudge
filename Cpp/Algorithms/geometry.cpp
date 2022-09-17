using o = double;
#define EPS 1e-6

// MAIN IMPORTS
// const double EPS = 1e-6;
// typedef pair<o, o> Point; typedef v(const Point&) Points;typedef v(const Points) vPoints;
// typedef pair<double, double> FPoint;
// #define x first #define y second #define linf 0x3f3f3f3f3f3f3f3f

// OTHER IMPORT
// #define MID(x, y) x + (y - x) / 2

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

Point center;
Point getCenter(const Point& p) {
  auto x = 0, y = 0;
  for (auto a : p) {
    x += a.x;
    y += a.y;
  }
  return Point(x / p.size(), y / p.size());
}

// clockwise sort - which point is less relative to a center
bool lessPt(const Point& a, const Point& b) {
  if (cmp(a.x, center.x) >= 0 && cmp(b.x, center.x) < 0) return true;
  if (cmp(a.x, center.x) < 0 && cmp(b.x, center.x) >= 0) return false;
  if (cmp(a.x, center.x) == 0 && cmp(b.x, center.x) == 0) {
    if (cmp(a.y, center.y) >= 0 || cmp(b.y, center.y) >= 0) return a.y > b.y;
    return b.y > a.y;
  }

  // compute the cross product of vectors (center -> a) x (center -> b)
  auto det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
  if (det != 0) return det < 0;

  // points a and b are on the same line from the center
  // check which point is closer to the center
  auto d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
  auto d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
  return d1 > d2;
}

struct FPoint {
  double x, y;
  Point(double x, double y): x(x), y(y) {}
};

// java didn't handle precision well,
// this method is just round the number to 5 decimal places
// change the number if you need more precise number
double round(double a) { return (double)round(a * 100000) / 100000; }

// rotate point p counter clock wise by rad respect to pivot
// this is the place where you want to use floating points instead of integer
// points
FPoint rotate(const FPoint& pivot, const FPoint& p, double rad) {
  double x = p.x - pivot.x, y = p.y - pivot.y;
  double newx = x * cos(rad) - y * sin(rad);
  double newy = x * sin(rad) + y * cos(rad);
  return Point(newx + pivot.x, newy + pivot.y);
}

Point rotate90CCW(const Point& pt) { return Point(-pt.y, pt.x); }  // 90 degrees from origin
Point rotate90CW(const Point& pt) { return Point(pt.y, -pt.x); }   // 90 degrees
Point rotate45(const Point& pt) { return Point(pt.y, pt.x); }      // 45 degrees

// ***IMPORTANT*** return 2x the area
o triangleArea(const Point& a, const Point& b, const Point& c) { return (-b.y * c.x + a.y * (-b.x + c.x) + a.x * (b.y - c.y) + b.x * c.y); }

// return true if point P lies on line AB
bool inSegment(const Point& a, const Point& b, const Point& p) {
  if (cmp(ccw(a, b, p), 0) != 0) return false;
  const auto$ tmp = sub(b, a);
  o dotProduct = dot(sub(p, a), tmp);
  return !(cmp(dotProduct, 0) < 0 || cmp(dotProduct, dot(tmp, tmp)) > 0);
}

// In: -1, On: 0, Out: 1
l inTriangle(const Point& a, const Point& b, const Point& c, const Point& p) {
  if (inSegment(a, b, p) || inSegment(a, c, p) || inSegment(b, c, p)) return 0;
  return cmp(abs(ccw(a, b, c)), abs(ccw(p, a, b)) + abs(ccw(p, b, c)) + abs(ccw(p, c, a))) == 0 ? -1 : 1;
}

// return true if the point p is inside or on the polygon
// O(lgn) approach!! Using the idea of binary search
l inConvexPolygon(const Point& p, const Points& &hull) {
  l a = 1, b = hull.size() - 2;
  const auto first = hull[0];
  while (a <= b) {
    auto mid = MID(a, b);
    auto cross1 = ccw(first, hull[mid], p);
    auto cross2 = ccw(first, hull[mid + 1], p);
    if (cmp(cross1, 0) >= 0 && cmp(cross2, 0) <= 0 && inTriangle(first, hull[mid], hull[mid + 1], p) <= 0)
      return inSegment(hull[mid], hull[mid + 1], p) ? 0 : -1;
    else if (cmp(cross1, 0) < 0)
      b = mid - 1;
    else
      a = mid + 1;
  }
  return 1;
}

/*=========//Need to Fix: O(lg n)
// lowerbound search
l right_ccw_search(l a, l b, const Point&s &hull, l y) {
  C "SRCH:" _ a _ b E;
  l mid = (a + b) / 2;
  if (a >= b) return mid;
  if (hull[mid].y >= y) return right_ccw_search(a, mid, hull, y);
  return right_ccw_search(mid + 1, b, hull, y);
}

// upperbound search
l left_ccw_search(l a, l b, const Point&s &hull, l y) {
  C "SCH:" _ a _ b E;
  l mid = (a + b) / 2;
  if (a >= b) return mid;
  if (hull[mid].y <= y) return left_ccw_search(a, mid, hull, y);
  return left_ccw_search(mid + 1, b, hull, y);
}

// Requires: CCW. Bottom-left is index 0. top = top right index
l inConvexPolygon(const Point& point, const Point&s &poly, l top) {
  if (point.y < poly[0].y || point.y > poly[top].y) return 1;
  //   if (poly.size() == 3) return inTriangle(poly[0], poly[1], poly[2],
  //   point);
  auto deg = ccw(point, poly[top], poly[0]);
  if (deg == 0) {
    if (point == poly[0] || point == poly[top]) return 0;
    return (top == 1 || top + 1 == poly.size()) ? 0 : -1;
  } else if (deg < 0) {
    auto itRight = right_ccw_search(0, top, poly, point.y);
    return sgn(ccw(poly[itRight], point, poly[itRight - 1]));
  } else {
    auto itLeft = left_ccw_search(top, poly.size() - 1, poly, point.y);
    return sgn(ccw(itLeft == poly.size() ? poly[0] : poly[itLeft - 1], point,
                   poly[itLeft]));
  }
}


//====*/

// A simple polygon is a polygon that does not intersect itself and has no holes.
// That is, it is a flat shape consisting of straight, non-intersecting line segments or
// "sides" that are joined pairwise to form a single closed path. If the sides intersect
// then the polygon is not simple.
// Output | In: -1, On: 0, Out: 1
l inSimplePolygon(const Point& point, const Points &poly) {
  auto n = poly.size(), windingNumber = 0;
  for (auto i = 0; i < n; ++i) {
    if (point == poly[i]) return 0;
    auto j = (i + 1) % n;
    if (poly[i].y == point.y && poly[j].y == point.y) {
      if (min(poly[i].x, poly[j].x) <= point.x && point.x <= max(poly[i].x, poly[j].x)) return 0;
    } else {
      auto below = poly[i].y < point.y;
      if (below != (poly[j].y < point.y)) {
        auto orientation = ccw(point, poly[j], poly[i]);
        if (orientation == 0) return 0;
        if (below == (orientation > 0)) windingNumber += below ? 1 : -1;
      }
    }
  }
  return windingNumber == 0 ? 1 : -1;
}

void rotateBottomToIndexZero(const Points &p) {
  auto n = p.size(), j = 0;
  for (auto i = 1; i < n; i++)
    if (lexComp(p[i], p[j])) j = i;
  rotate(p.begin(), p.begin() + j, p.end());
}

bool isConvex(const Points &p, l n) {
  if (n <= 3) return false;  // a point/n=2 or a line/n=3 is not convex
  auto isLeft = ccw(p[0], p[1], p[2]);
  for (auto i = 0; i < n - 1; i++)                                                    // then compare with the others
    if (ccw(p[i], p[i + 1], p[(i + 2) == n ? 1 : i + 2]) != isLeft) return false;  // different sign -> this polygon is concave
  return true;
}

l bottomLeftIndex(const Points &p, l n) {
  auto firstIndex = 0;
  for (auto i = 1; i < n; i++) {
    if (p[i].y < p[firstIndex].y || (p[i].y == p[firstIndex].y && p[i].x < p[firstIndex].x)) firstIndex = i;
  }
  return firstIndex;
}
l topRightIndex(const Points &p, l n) {
  auto index = 0;
  for (auto i = 1; i < n; i++) {
    if (p[i].y > p[index].y || (p[i].y == p[index].y && p[i].x > p[index].x)) index = i;
  }
  return index;
}

/ return the convex hull of a set of points
// required: firstPoint, ccw(),cross(),sub(),angleCmp
// Args: p - input points, n - length of points
// out - required buffer size of 2*p.size()
// Complexity: n log n
void convexHull(Points& p, l n, Points& out, l& outLength) {
    std::swap(p[0], p[bottomLeftIndex(p, n)]);
    firstPoint = p[0];

    sort(p.begin() + 1, p.begin() + n, angleCmp);
    auto q = Points();
    q.emplace_back(p[0]);
    // remove colinear points
    for (auto i = 2; i < n; i++)
        if (ccw(firstPoint, p[i - 1], p[i]) != 0) {
        q.emplace_back(p[i - 1]);
        }
    q.emplace_back(p[n - 1]);
    n = q.size();
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

double polygonDiameter(const Points &p, l n) {
  if (n < 2)
    return 0;
  else if (n == 2)
    return sqrt(distSq(p[0], p[1]));
  else {
    auto i = n - 1, j = 0, k = 1;
    auto res = 0;
    while (abs(ccw(p[i], p[j], p[k + 1])) > abs(ccw(p[i], p[j], p[k]))) {
      k++;
    }
    i = 0, j = k;
    while (i <= k && j < n) {
      res = max(distSq(p[i], p[j]), res);
      while (j < n - 1 && abs(ccw(p[i], p[i + 1], p[j + 1])) > abs(ccw(p[i], p[i + 1], p[j]))) {
        res = max(distSq(p[i], p[++j]), res);
      }
      i++;
    }
    return sqrt(res);
  }
}

// Adds a point p to given convex hull O(n)
void addPointHull(const Points &hull, const Point& p, l n) {
  if (inSimplePolygon(p, hull) == -1) return;
  Points ret;
  // point having minimum distance from the point p
  auto h = 0;
  for (auto i = 1; i < n; i++)
    if (distSq(p, hull[i]) < distSq(p, hull[h])) h = i;

  // Find the tangents
  auto up = (h + 1) % n, low = (n + h - 1) % n;
  while (ccw(p, hull[up], hull[(up + 1) % n]) >= 0) up = (up + 1) % n;
  while (ccw(p, hull[low], hull[(n + low - 1) % n]) <= 0) low = (n + low - 1) % n;

  // making the final hull by traversing points
  // from up to low of given convex hull.
  auto curr = up;
  ret.emplace_back(hull[curr]);
  while (curr != low) ret.emplace_back(hull[curr = (curr + 1) % n]);

  // Modify the original vector
  ret.emplace_back(p);
  hull.clear();
  for (auto i = 0; i < ret.size(); i++) hull.emplace_back(ret[i]);
}

// return the area of a polygon O(n)
double polygonArea(const Points &list) {
  double area = 0;
  for (auto i = 0; i < list.size(); i++) area += cross(list[i], list[(i + 1) % list.size()]);
  return fabs(area) / 2.0;
}

void clockWiseSort(const Points &p) { sort(p.begin(), p.end(), lessPt); }

// same as ccw, this just return true or false
bool leftTurn(const Point& a, const Point& b, const Point& c) { return cmp(cross(sub(b, a), sub(c, a)), 0) > 0; }

// return true if line AB intersect with line CD
//***IMPORTANT*** does not include the case that one end of a line in on another
// line
bool isIntersect(const Point& a, const Point& b, const Point& c, const Point& d) { return leftTurn(a, b, c) != leftTurn(a, b, d) && leftTurn(c, d, a) != leftTurn(c, d, b); }

// line segment p-q intersect with line A-B. Name: lineIntersectSeg
Point ptLineSegIntersect(const Point& p, const Point& q, const Point& A, const Point& B) {
  o a = B.y - A.y;
  o b = A.x - B.x;
  o c = B.x * A.y - A.x * B.y;
  o u = abs(a * p.x + b * p.y + c);
  o v = abs(a * q.x + b * q.y + c);
  return Point((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v));
}

Point ptLineLineIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
  o m1 = a.x != b.x ? (a.y - b.y) / (a.x - b.x) : linf, m2 = c.x != d.x ? (c.y - d.y) / (c.x - d.x) : linf;
  if (m1 != m2) {
    o x = (m1 * a.x - m2 * c.x + c.y - a.y) / (m1 - m2);
    x = m1 == linf ? a.x : m2 == linf ? c.x : x;
    return Point(x, m2 == linf ? m1 * x + (a.y - m1 * a.x) : m2 * x + (c.y - m2 * c.x));
  }
  return Point(linf, linf);
}

l ptSegSegIntersect(const Point& a, const Point& b, const Point& c, const Point& d, const Point& &res) {
  Point a2 = sub(b, a), c2 = sub(d, c);
  if (cross(a2, c2) == 0) {
    if (cross(sub(c, a), a2) == 0) return 1;  // colinear
    return -2;                                // parallel
  }
  o t = cross(sub(c, a), c2) / cross(a2, c2);
  o u = cross(sub(c, a), a2) / cross(a2, c2);
  if (cmp(t, 0) < 0 || cmp(t, 1) > 0 || cmp(u, 0) < 0 || cmp(u, 1) > 0) return -1;  // no intersection
  Point ans = add(a, scale(a2, t));
  res.x = ans.x;
  res.y = ans.y;
  return 0;
}

// Requirements: CW, No holes
// Points intersectionPolygon(const Points &a, const Point&s &b) {
//   l n = a.size(), m = b.size(), i, j;
//   vl inout = vl(m, 0);
//   fpp(i, 0, n) inout[i] = inSimplePolygon(b[i], a);
// }

// This functions clips all the edges w.r.t one clip
// edge of clipping area
void clip(const Points &poly, const Point& a, const Point& b) {
  Points pts;
  l i, n = poly.size();
  for (auto i = 0; i < n; i++) {
    l k = (i + 1) % n;
    l i_pos = ccw(a, b, poly[i]);
    l k_pos = ccw(a, b, poly[k]);
    // Case 1 : When both points are inside
    if (i_pos < 0 && k_pos < 0) {
      pts.emplace_back(poly[k].x, poly[k].y);
    }
    // Case 2: When only first point is outside
    else if (i_pos >= 0 && k_pos < 0) {
      Point pt = ptLineLineIntersect(poly[i], poly[k], a, b);
      pts.emplace_back(pt.x, pt.y);
      pts.emplace_back(poly[k].x, poly[k].y);
    }
    // Case 3: When only second point is outside
    else if (i_pos < 0 && k_pos >= 0) {
      Point pt = ptLineLineIntersect(poly[i], poly[k], a, b);
      pts.emplace_back(pt.x, pt.y);
    }
  }
  poly.clear();
  for (auto i = 0; i < pts.size(); i++) poly.emplace_back(const Point&(pts[i].x, pts[i].y));
}

// Implements Sutherland–Hodgman algorithm
Points suthHodgClip(const Points &poly, l n, const Point&s clipper, l m) {
  l i;
  Points res = Points(n);
  for (auto i = 0; i < n; i++) res[i] = Point(poly[i].x, poly[i].y);
  for (auto i = 0; i < m; i++) clip(res, clipper[i], clipper[(i + 1) % m]);
  return res;
}

// return true if it is a simple polygon
bool isSimplePolygon(const Points list) {
  l i, j;
  for (auto i = 0; i < list.size(); i++) {
    for (l j = 0; i < list.size(); i++) {
      if (abs(i - j) <= 1 || abs(i - j) >= list.size() - 1) continue;
      if (isIntersect(list[i], list[(i + 1) % list.size()], list[j], list[(j + 1) % list.size()])) return false;
    }
  }
  return true;
}

// cuts polygon Q along the line formed by point a -> point b
//***IMPORTANT*** the last point must be the same as the first point
Points cutPolygon(const Point& a, const Point& b, const Point&s Q) {
  Points P = Points();
  l i;
  for (auto i = 0; i < Q.size(); i++) {
    double left1 = cross(sub(b, a), sub(Q[i], a)), left2 = 0;
    if (i != Q.size() - 1) left2 = cross(sub(b, a), sub(Q[i + 1], a));
    if (left1 > -EPS) P.emplace_back(Q[i]);  // Q[i] is on the left of ab
    if (left1 * left2 < -EPS)                // edge (Q[i], Q[i+1]) crosses line ab
      P.emplace_back(ptLineSegIntersect(Q[i], Q[i + 1], a, b));
  }
  if (!P.empty() && !(P[P.size() - 1].x == P[0].x && P[P.size() - 1].y == P[0].y)) P.emplace_back(P[0]);
  // make P's first point = P's last point
  return P;
}

int main() {
  Points cPointrds = {Point(10, 10), const Point&(0, 0), const Point&(0, 10), const Point&(10, 0), const Point&(5, 5)};
  // center = getCenter(cPointrds);
  // C "Center: " << center.x << " " << center.y E;
  // ;
  // clockWiseSort(cPointrds);
  // for (auto i : cPointrds) {
  //   C i.x << " " << i.y E;
  // }
  // C "Simple Polygon: " << isSimplePolygon(cPointrds) E;
  cout << "Hull: "
       << "\n";
  auto hull = convexHull(cPointrds);
  l h = hull.size();
  for (auto i : hull) cout << i.x << " " << i.y << "\n";
  // Point newPt = Point(10.5, 11);
  // addPointHull(hull, newPt, h);
  // C "New HULL - Adding: " _ newPt.x _ newPt.y E;
  // for (auto i : hull) C i.x << " " << i.y E;
  Points pts = {Point(8, 8), const Point&(7, 3), const Point&(0, 10), const Point&(2, 20), const Point&(11, 1)};

  cout << "\nInside Simple HULL"
       << "\n";
  for (const Point& pt : pts) cout << pt.x << " " << pt.y << " " << inSimplePolygon(pt, hull) << "\n";
  cout << "\nInside Convex HULL"
       << "\n";
  for (const Point& pt : pts) cout << pt.x << pt.y << " " << inConvexPolygon(pt, hull) << "\n";

  // Points tri1 = Points(Point(2, n2),   Point(2, 4), const Point&(4, 4),
  //                Point(3.5, 3), const Point&(4, 2), const Point&(2, 2));
  // Points tri2 =
  //     Points(Point(3, 5), const Point&(4, 5), const Point&(4, 1), const Point&(3,
  //     1);
  // C "Clip: ";
  // suthHodgClip(tri1, tri1.size(), tri2, tri2.size());
  // C "" E;

  // Point pt1 = Point(0, 0);
  // Point pt2 = Point(2, 10);
  // Point pt3 = Point(0, 5);
  // Point pt4 = Point(1, -1);
  // Point intersect;
  // if (ptSegSegIntersect(pt1, pt2, pt3, pt4, intersect) == 0)
  //   C "Intersecting:" _ intersect.x _ intersect.y E;
}