#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
using namespace std;
typedef long long l;
typedef double o;

const double EPS = 1e-6;
typedef pair<o, o> oo;
typedef v(oo) voo;
typedef v(voo) vvoo;
typedef pair<oo, oo> seg;
typedef v(seg) vseg;
#define xx first
#define yy second

oo add(oo a, oo b) { return make_pair(a.xx + b.xx, a.yy + b.yy); }
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

bool ptSegSegIntersect(oo a, oo b, oo c, oo d) {
  oo a2 = sub(b, a), c2 = sub(d, c);
  o t = cross(sub(c, a), c2) / cross(a2, c2);
  o u = cross(sub(c, a), a2) / cross(a2, c2);
  if (cmp(t, 0) < 0 || cmp(t, 1) > 0 || cmp(u, 0) < 0 || cmp(u, 1) > 0)
    return false;  // no intersection
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, i, j, k;
  cin >> n;
  while (n > 0) {
    vseg segs = vseg(n);
    fpp(i, 0, n) {
      cin >> segs[i].first.xx >> segs[i].first.yy >> segs[i].second.xx >>
          segs[i].second.yy;
    }
    l count = 0;
    fpp(i, 0, n) {
      fpp(j, i + 1, n) {
        fpp(k, j + 1, n) {
          if (ptSegSegIntersect(segs[i].first, segs[i].second, segs[j].first,
                                segs[j].second) &&
              ptSegSegIntersect(segs[i].first, segs[i].second, segs[k].first,
                                segs[k].second) &&
              ptSegSegIntersect(segs[k].first, segs[k].second, segs[j].first,
                                segs[j].second)) {
            count++;
          }
        }
      }
    }
    C count E;
    cin >> n;
  }
}
