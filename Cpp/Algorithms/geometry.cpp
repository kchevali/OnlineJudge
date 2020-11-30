#include "../all.cpp"

// MAIN IMPORTS
// const double EPS = 1e-6;
// typedef pair<o, o> oo; typedef v(oo) voo;typedef v(voo) vvoo;
// typedef pair<double, double> dd;
// #define xx first #define yy second #define linf 0x3f3f3f3f3f3f3f3f

// OTHER IMPORT
// #define MID(x, y) x + (y - x) / 2

oo add(oo a, oo b) { return make_pair(a.xx + b.xx, a.yy + b.yy); }
oo sub(oo a, oo b) { return make_pair(a.xx - b.xx, a.yy - b.yy); }
o dot(oo a, oo b) { return a.xx * b.xx + a.yy * b.yy; }
o cross(oo a, oo b) { return a.xx * b.yy - a.yy * b.xx; }
oo scl(oo a, o b) { return make_pair(a.xx * b, a.yy * b); }
l cmp(o a, o b) { return abs(a - b) < EPS ? 0 : (a > b ? 1 : -1); }
l sgn(l val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }
o sqrLen(oo a) { return dot(a, a); }
o distSq(oo a, oo b) { return (a.xx - b.xx) * (a.xx - b.xx) + (a.yy - b.yy) * (a.yy - b.yy); }
// left: postive // right: negative // colinear: 0
o ccw(oo p, oo a, oo b) { return cross(sub(a, p), sub(b, p)); }
oo firstPoint;
bool angleCmp(const oo a, const oo b) {
  l deg = ccw(a, b, firstPoint);
  return deg == 0 ? (distSq(firstPoint, a) < distSq(firstPoint, b)) : deg > 0;
}
bool lexComp(oo a, oo b) { return a.yy < b.yy || (a.yy == b.yy && a.xx < b.xx); }

oo center;
oo getCenter(voo &p) {
  o x = 0, y = 0;
  for (auto a : p) {
    x += a.xx;
    y += a.yy;
  }
  return make_pair(x / p.size(), y / p.size());
}

// clockwise sort - which point is less relative to a center
bool lessPt(const oo a, const oo b) {
  if (cmp(a.xx, center.xx) >= 0 && cmp(b.xx, center.xx) < 0) return true;
  if (cmp(a.xx, center.xx) < 0 && cmp(b.xx, center.xx) >= 0) return false;
  if (cmp(a.xx, center.xx) == 0 && cmp(b.xx, center.xx) == 0) {
    if (cmp(a.yy, center.yy) >= 0 || cmp(b.yy, center.yy) >= 0) return a.yy > b.yy;
    return b.yy > a.yy;
  }

  // compute the cross product of vectors (center -> a) x (center -> b)
  l det = (a.xx - center.xx) * (b.yy - center.yy) - (b.xx - center.xx) * (a.yy - center.yy);
  if (det != 0) return det < 0;

  // points a and b are on the same line from the center
  // check which point is closer to the center
  l d1 = (a.xx - center.xx) * (a.xx - center.xx) + (a.yy - center.yy) * (a.yy - center.yy);
  l d2 = (b.xx - center.xx) * (b.xx - center.xx) + (b.yy - center.yy) * (b.yy - center.yy);
  return d1 > d2;
}

// java didn't handle precision well,
// this method is just round the number to 5 decimal places
// change the number if you need more precise number
double round(double a) { return (double)round(a * 100000) / 100000; }

// rotate point p counter clock wise by rad respect to pivot
// this is the place where you want to use floating points instead of integer
// points
dd rotate(dd pivot, dd p, double rad) {
  double x = p.xx - pivot.xx, y = p.yy - pivot.yy;
  double newx = x * cos(rad) - y * sin(rad);
  double newy = x * sin(rad) + y * cos(rad);
  return make_pair(newx + pivot.xx, newy + pivot.yy);
}

oo rotate90CCW(oo pt) { return {-pt.yy, pt.xx}; }  // 90 degrees from origin
oo rotate90CW(oo pt) { return {pt.yy, -pt.xx}; }   // 90 degrees
oo rotate45(oo pt) { return {pt.yy, pt.xx}; }      // 45 degrees

// ***IMPORTANT*** return 2x the area
o triangleArea(oo a, oo b, oo c) { return (-b.yy * c.xx + a.yy * (-b.xx + c.xx) + a.xx * (b.yy - c.yy) + b.xx * c.yy); }

// return true if point P lies on line AB
bool inSegment(oo a, oo b, oo p) {
  if (cmp(ccw(a, b, p), 0) != 0) return false;
  oo tmp = sub(b, a);
  o dotProduct = dot(sub(p, a), tmp);
  return !(cmp(dotProduct, 0) < 0 || cmp(dotProduct, dot(tmp, tmp)) > 0);
}

// In: -1, On: 0, Out: 1
l inTriangle(oo a, oo b, oo c, oo p) {
  if (inSegment(a, b, p) || inSegment(a, c, p) || inSegment(b, c, p)) return 0;
  return cmp(abs(ccw(a, b, c)), abs(ccw(p, a, b)) + abs(ccw(p, b, c)) + abs(ccw(p, c, a))) == 0 ? -1 : 1;
}

// return true if the point p is inside or on the polygon
// O(lgn) approach!! Using the idea of binary search
l inConvexPolygon(oo p, voo &hull) {
  l a = 1, b = hull.size() - 2;
  oo first = hull[0];
  while (a <= b) {
    l mid = MID(a, b);
    o cross1 = ccw(first, hull[mid], p);
    o cross2 = ccw(first, hull[mid + 1], p);
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
l right_ccw_search(l a, l b, voo &hull, l y) {
  C "SRCH:" _ a _ b E;
  l mid = (a + b) / 2;
  if (a >= b) return mid;
  if (hull[mid].yy >= y) return right_ccw_search(a, mid, hull, y);
  return right_ccw_search(mid + 1, b, hull, y);
}

// upperbound search
l left_ccw_search(l a, l b, voo &hull, l y) {
  C "SCH:" _ a _ b E;
  l mid = (a + b) / 2;
  if (a >= b) return mid;
  if (hull[mid].yy <= y) return left_ccw_search(a, mid, hull, y);
  return left_ccw_search(mid + 1, b, hull, y);
}

// Requires: CCW. Bottom-left is index 0. top = top right index
l inConvexPolygon(oo point, voo &poly, l top) {
  if (point.yy < poly[0].yy || point.yy > poly[top].yy) return 1;
  //   if (poly.size() == 3) return inTriangle(poly[0], poly[1], poly[2],
  //   point);
  auto deg = ccw(point, poly[top], poly[0]);
  if (deg == 0) {
    if (point == poly[0] || point == poly[top]) return 0;
    return (top == 1 || top + 1 == poly.size()) ? 0 : -1;
  } else if (deg < 0) {
    auto itRight = right_ccw_search(0, top, poly, point.yy);
    return sgn(ccw(poly[itRight], point, poly[itRight - 1]));
  } else {
    auto itLeft = left_ccw_search(top, poly.size() - 1, poly, point.yy);
    return sgn(ccw(itLeft == poly.size() ? poly[0] : poly[itLeft - 1], point,
                   poly[itLeft]));
  }
}


//====*/

// In: -1, On: 0, Out: 1
l inSimplePolygon(oo point, voo &poly) {
  l n = poly.size(), windingNumber = 0;
  for (int i = 0; i < n; ++i) {
    if (point == poly[i]) return 0;
    l j = (i + 1) % n;
    if (poly[i].yy == point.yy && poly[j].yy == point.yy) {
      if (min(poly[i].xx, poly[j].xx) <= point.xx && point.xx <= max(poly[i].xx, poly[j].xx)) return 0;
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

void rotateBottomToIndexZero(voo &p) {
  l n = p.size(), j = 0, i;
  for (l i = 1; i < n; i++)
    if (lexComp(p[i], p[j])) j = i;
  rotate(p.begin(), p.begin() + j, p.end());
}

bool isConvex(const voo &p, l n) {
  if (n <= 3) return false;  // a point/n=2 or a line/n=3 is not convex
  bool isLeft = ccw(p[0], p[1], p[2]);
  l i;                                                                             // remember one result
  for (l i = 0; i < n - 1; i++)                                                    // then compare with the others
    if (ccw(p[i], p[i + 1], p[(i + 2) == n ? 1 : i + 2]) != isLeft) return false;  // different sign -> this polygon is concave
  return true;
}

l bottomLeftIndex(voo &p, l n) {
  l i, firstIndex = 0;
  for (l i = 1; i < n; i++) {
    if (p[i].yy < p[firstIndex].yy || (p[i].yy == p[firstIndex].yy && p[i].xx < p[firstIndex].xx)) firstIndex = i;
  }
  return firstIndex;
}
l topRightIndex(voo &p, l n) {
  l i, index = 0;
  for (l i = 1; i < n; i++) {
    if (p[i].yy > p[index].yy || (p[i].yy == p[index].yy && p[i].xx > p[index].xx)) index = i;
  }
  return index;
}

// return the convex hull of a set of points
// required: firstPoint, ccw(),cross(),sub(),angleCmp
// Complexity: n log n
voo convexHull(voo &p) {
  l i, n = p.size();
  swap(p[0], p[bottomLeftIndex(p, n)]);
  firstPoint = p[0];

  sort(p.begin() + 1, p.end(), angleCmp);
  voo q = voo();
  q.emplace_back(p[0]);
  // remove colinear points
  for (l i = 2; i < n; i++)
    if (ccw(firstPoint, p[i - 1], p[i]) != 0) {
      q.emplace_back(p[i - 1]);
    }
  q.emplace_back(p[n - 1]);
  n = q.size();
  if (n <= 2) return q[0] == q[1] ? voo{q[0]} : q;

  voo hull = voo(2 * n);
  for (l i = 0; i < 3; i++) hull[i] = q[i];
  l h = 3;
  for (l i = 3; i < n; i++) {
    while (ccw(hull[h - 2], hull[h - 1], q[i]) <= 0) h--;
    hull[h++] = q[i];
  }
  return voo(hull.begin(), hull.begin() + h);
}

double polygonDiameter(voo &p, l n) {
  if (n < 2)
    return 0;
  else if (n == 2)
    return sqrt(distSq(p[0], p[1]));
  else {
    l i = n - 1, j = 0, k = 1;
    o res = 0;
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
void addPointHull(voo &hull, oo p, l n) {
  if (inSimplePolygon(p, hull) == -1) return;
  voo ret;
  // point having minimum distance from the point p
  l h = 0, i, j;
  for (l i = 1; i < n; i++)
    if (distSq(p, hull[i]) < distSq(p, hull[h])) h = i;

  // Find the tangents
  l up = (h + 1) % n, low = (n + h - 1) % n;
  while (ccw(p, hull[up], hull[(up + 1) % n]) >= 0) up = (up + 1) % n;
  while (ccw(p, hull[low], hull[(n + low - 1) % n]) <= 0) low = (n + low - 1) % n;

  // making the final hull by traversing points
  // from up to low of given convex hull.
  l curr = up;
  ret.emplace_back(hull[curr]);
  while (curr != low) ret.emplace_back(hull[curr = (curr + 1) % n]);

  // Modify the original vector
  ret.emplace_back(p);
  hull.clear();
  for (l i = 0; i < ret.size(); i++) hull.emplace_back(ret[i]);
}

// return the area of a polygon O(n)
double polygonArea(voo &list) {
  double area = 0;
  l i;
  for (l i = 0; i < list.size(); i++) area += cross(list[i], list[(i + 1) % list.size()]);
  return fabs(area) / 2.0;
}

void clockWiseSort(voo &p) { sort(p.begin(), p.end(), lessPt); }

// same as ccw, this just return true or false
bool leftTurn(oo a, oo b, oo c) { return cmp(cross(sub(b, a), sub(c, a)), 0) > 0; }

// return true if line AB intersect with line CD
//***IMPORTANT*** does not include the case that one end of a line in on another
// line
bool isIntersect(oo a, oo b, oo c, oo d) { return leftTurn(a, b, c) != leftTurn(a, b, d) && leftTurn(c, d, a) != leftTurn(c, d, b); }

// line segment p-q intersect with line A-B. Name: lineIntersectSeg
oo ptLineSegIntersect(oo p, oo q, oo A, oo B) {
  o a = B.yy - A.yy;
  o b = A.xx - B.xx;
  o c = B.xx * A.yy - A.xx * B.yy;
  o u = abs(a * p.xx + b * p.yy + c);
  o v = abs(a * q.xx + b * q.yy + c);
  return make_pair((p.xx * v + q.xx * u) / (u + v), (p.yy * v + q.yy * u) / (u + v));
}

oo ptLineLineIntersect(oo a, oo b, oo c, oo d) {
  o m1 = a.xx != b.xx ? (a.yy - b.yy) / (a.xx - b.xx) : linf, m2 = c.xx != d.xx ? (c.yy - d.yy) / (c.xx - d.xx) : linf;
  if (m1 != m2) {
    o x = (m1 * a.xx - m2 * c.xx + c.yy - a.yy) / (m1 - m2);
    x = m1 == linf ? a.xx : m2 == linf ? c.xx : x;
    return make_pair(x, m2 == linf ? m1 * x + (a.yy - m1 * a.xx) : m2 * x + (c.yy - m2 * c.xx));
  }
  return make_pair(linf, linf);
}

l ptSegSegIntersect(oo a, oo b, oo c, oo d, oo &res) {
  oo a2 = sub(b, a), c2 = sub(d, c);
  if (cross(a2, c2) == 0) {
    if (cross(sub(c, a), a2) == 0) return 1;  // colinear
    return -2;                                // parallel
  }
  o t = cross(sub(c, a), c2) / cross(a2, c2);
  o u = cross(sub(c, a), a2) / cross(a2, c2);
  if (cmp(t, 0) < 0 || cmp(t, 1) > 0 || cmp(u, 0) < 0 || cmp(u, 1) > 0) return -1;  // no intersection
  oo ans = add(a, scl(a2, t));
  res.xx = ans.xx;
  res.yy = ans.yy;
  return 0;
}

// Requirements: CW, No holes
// voo intersectionPolygon(voo &a, voo &b) {
//   l n = a.size(), m = b.size(), i, j;
//   vl inout = vl(m, 0);
//   fpp(i, 0, n) inout[i] = inSimplePolygon(b[i], a);
// }

// This functions clips all the edges w.r.t one clip
// edge of clipping area
void clip(voo &poly, oo a, oo b) {
  voo pts;
  l i, n = poly.size();
  for (l i = 0; i < n; i++) {
    l k = (i + 1) % n;
    l i_pos = ccw(a, b, poly[i]);
    l k_pos = ccw(a, b, poly[k]);
    // Case 1 : When both points are inside
    if (i_pos < 0 && k_pos < 0) {
      pts.emplace_back(poly[k].xx, poly[k].yy);
    }
    // Case 2: When only first point is outside
    else if (i_pos >= 0 && k_pos < 0) {
      oo pt = ptLineLineIntersect(poly[i], poly[k], a, b);
      pts.emplace_back(pt.xx, pt.yy);
      pts.emplace_back(poly[k].xx, poly[k].yy);
    }
    // Case 3: When only second point is outside
    else if (i_pos < 0 && k_pos >= 0) {
      oo pt = ptLineLineIntersect(poly[i], poly[k], a, b);
      pts.emplace_back(pt.xx, pt.yy);
    }
  }
  poly.clear();
  for (l i = 0; i < pts.size(); i++) poly.emplace_back(make_pair(pts[i].xx, pts[i].yy));
}

// Implements Sutherland–Hodgman algorithm
voo suthHodgClip(voo &poly, l n, voo clipper, l m) {
  l i;
  voo res = voo(n);
  for (l i = 0; i < n; i++) res[i] = make_pair(poly[i].xx, poly[i].yy);
  for (l i = 0; i < m; i++) clip(res, clipper[i], clipper[(i + 1) % m]);
  return res;
}

// return true if it is a simple polygon
bool isSimplePolygon(voo list) {
  l i, j;
  for (l i = 0; i < list.size(); i++) {
    for (l j = 0; i < list.size(); i++) {
      if (abs(i - j) <= 1 || abs(i - j) >= list.size() - 1) continue;
      if (isIntersect(list[i], list[(i + 1) % list.size()], list[j], list[(j + 1) % list.size()])) return false;
    }
  }
  return true;
}

// cuts polygon Q along the line formed by point a -> point b
//***IMPORTANT*** the last point must be the same as the first point
voo cutPolygon(oo a, oo b, voo Q) {
  voo P = voo();
  l i;
  for (l i = 0; i < Q.size(); i++) {
    double left1 = cross(sub(b, a), sub(Q[i], a)), left2 = 0;
    if (i != Q.size() - 1) left2 = cross(sub(b, a), sub(Q[i + 1], a));
    if (left1 > -EPS) P.emplace_back(Q[i]);  // Q[i] is on the left of ab
    if (left1 * left2 < -EPS)                // edge (Q[i], Q[i+1]) crosses line ab
      P.emplace_back(ptLineSegIntersect(Q[i], Q[i + 1], a, b));
  }
  if (!P.empty() && !(P[P.size() - 1].xx == P[0].xx && P[P.size() - 1].yy == P[0].yy)) P.emplace_back(P[0]);
  // make P's first point = P's last point
  return P;
}

int main() {
  voo coords = {make_pair(10, 10), make_pair(0, 0), make_pair(0, 10), make_pair(10, 0), make_pair(5, 5)};
  // center = getCenter(coords);
  // C "Center: " << center.xx << " " << center.yy E;
  // ;
  // clockWiseSort(coords);
  // for (auto i : coords) {
  //   C i.xx << " " << i.yy E;
  // }
  // C "Simple Polygon: " << isSimplePolygon(coords) E;
  cout << "Hull: "
       << "\n";
  auto hull = convexHull(coords);
  l h = hull.size();
  for (auto i : hull) cout << i.xx << " " << i.yy << "\n";
  // oo newPt = make_pair(10.5, 11);
  // addPointHull(hull, newPt, h);
  // C "New HULL - Adding: " _ newPt.xx _ newPt.yy E;
  // for (auto i : hull) C i.xx << " " << i.yy E;
  voo pts = {make_pair(8, 8), make_pair(7, 3), make_pair(0, 10), make_pair(2, 20), make_pair(11, 1)};

  cout << "\nInside Simple HULL"
       << "\n";
  for (oo pt : pts) cout << pt.xx << " " << pt.yy << " " << inSimplePolygon(pt, hull) << "\n";
  cout << "\nInside Convex HULL"
       << "\n";
  for (oo pt : pts) cout << pt.xx << pt.yy << " " << inConvexPolygon(pt, hull) << "\n";

  // voo tri1 = voo{make_pair(2, n2),   make_pair(2, 4), make_pair(4, 4),
  //                make_pair(3.5, 3), make_pair(4, 2), make_pair(2, 2)};
  // voo tri2 =
  //     voo{make_pair(3, 5), make_pair(4, 5), make_pair(4, 1), make_pair(3,
  //     1)};
  // C "Clip: ";
  // suthHodgClip(tri1, tri1.size(), tri2, tri2.size());
  // C "" E;

  // oo pt1 = make_pair(0, 0);
  // oo pt2 = make_pair(2, 10);
  // oo pt3 = make_pair(0, 5);
  // oo pt4 = make_pair(1, -1);
  // oo intersect;
  // if (ptSegSegIntersect(pt1, pt2, pt3, pt4, intersect) == 0)
  //   C "Intersecting:" _ intersect.xx _ intersect.yy E;
}