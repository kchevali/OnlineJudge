#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
const double EPS = 1e-6;
using namespace std;
typedef long long l;
typedef long long o;
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

oo sub(oo a, oo b) { return make_pair(a.first - b.first, a.second - b.second); }
o dot(oo a, oo b) { return a.first * b.first + a.second * b.second; }
o cross(oo a, oo b) { return a.first * b.second - a.second * b.first; }
l cmp(o a, o b) { return abs(a - b) < EPS ? 0 : (a > b ? 1 : -1); }
o ccw(oo a, oo b, oo c) { return cross(sub(b, a), sub(c, a)); }
o distSq(oo a, oo b) {
  return (a.xx - b.xx) * (a.xx - b.xx) + (a.yy - b.yy) * (a.yy - b.yy);
}
oo firstPoint;
bool angleCmp(const oo a, const oo b) {
  l deg = ccw(a, b, firstPoint);
  // C "CHECKING - A:" _ a.xx _ a.yy _ "B:" _ b.xx _ b.yy _ "DEG:" _ deg E;
  return deg == 0 ? (distSq(firstPoint, a) < distSq(firstPoint, b)) : deg > 0;
}

// voo convexHull(voo &p) {
//   l i, firstIndex = 0, n = p.size();
//   fpp(i, 1, n) {
//     if (p[i].second < p[firstIndex].second ||
//         (p[i].second == p[firstIndex].second &&
//          p[i].first < p[firstIndex].first))
//       firstIndex = i;
//   }
//   voo hull = voo(2 * n);
//   fpp(i, 0, 3) hull[i] = p[i];
//   l index = 3;
//   fpp(i, 3, n) {
//     while (ccw(hull[index - 2], hull[index - 1], p[i]) <= 0) {
//       index--;
//     }
//     hull[index] = p[i];

//   }
// }

l smallestIndex(voo &p, l n) {
  l i, firstIndex = 0;
  fpp(i, 1, n) {
    if (p[i].yy < p[firstIndex].yy ||
        (p[i].yy == p[firstIndex].yy && p[i].xx < p[firstIndex].xx))
      firstIndex = i;
  }
  return firstIndex;
}

voo convexHull(voo &p) {
  l i, n = p.size();
  swap(p[0], p[smallestIndex(p, n)]);
  firstPoint = p[0];

  sort(p.begin() + 1, p.end(), angleCmp);
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, i, j;
  read(n);
  while (n) {
    voo pts = voo(n);
    fpp(i, 0, n) {
      l x, y;
      read(x);
      read(y);
      pts[i] = make_pair(x, y);
    }
    auto hull = convexHull(pts);
    C hull.size() E;
    for (auto h : hull) C h.first _ h.second E;
    read(n);
  }
}
/*
8
0 0
1 4
3 1
3 3
5 5
5 2
7 0
9 6


 */
