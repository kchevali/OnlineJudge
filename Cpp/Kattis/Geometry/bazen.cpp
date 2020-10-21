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
typedef double o;
typedef pair<o, o> oo;
typedef v(oo) voo;

o triangleArea(oo a, oo b, oo c) {
  return abs(a.first * (b.second - c.second) + b.first * (c.second - a.second) +
             c.first * (a.second - b.second)) /
         2.0;
}
oo startPoint;

oo search(bool isHorizontal, bool isVertical, oo corner) {
  o x = 0.0, y = 0.0, pt = 0.0;
  l i;
  fpp(i, 0, 250000) {
    if (isHorizontal) {
      x = pt;
    } else if (isVertical) {
      y = pt;
    } else {
      x = pt;
      y = 250.0 - pt;
    }
    oo newPoint = make_pair(x, y);
    o area = triangleArea(startPoint, corner, newPoint);
    // C newPoint.first _ newPoint.second _ area E;
    if (abs(area - 15625.0) < 0.1) return newPoint;
    pt += 0.001;
  }
  return make_pair(-1, -1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l x, y;
  cin >> x >> y;

  startPoint = make_pair((double)x, (double)y);
  oo ans = search(true, false, make_pair(x == 0 ? 0.0 : 250.0, 0.0));
  if (ans.first == -1)
    ans = search(false, true, make_pair(0.0, y == 0 ? 0.0 : 250.0));
  if (ans.first == -1)
    ans = search(false, false,
                 make_pair(x == 0 ? 0.0 : 250.0, x == 0 ? 250.0 : 0.0));
  dc(2) ans.first _ ans.second E;
}

/*
0 250
250 0
0 0
125 125
125 0
0 125

190 0



 */
