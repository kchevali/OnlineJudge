// Submitted to Kattis
#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define pc putchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define DC(x) cout << fixed << setprecision(x) <<

using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

double x, y;

inline double dis(double a, double b) {
  return sqrt((a - x) * (a - x) + (b - y) * (b - y));
}

inline bool ib(double x, double a, double b) { return x >= a && x <= b; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  double x1, y1, x2, y2;
  cin >> x >> y >> x1 >> y1 >> x2 >> y2;

  tie(x1, x2) = minmax(x1, x2), tie(y1, y2) = minmax(y1, y2);
  if (ib(x, x1, x2))
    DC(3)(y <= y1 ? y1 - y : y - y2) E;
  else if (ib(y, y1, y2))
    DC(3)(x <= x1 ? x1 - x : x - x2) E;
  else
    DC(3) min({dis(x1, y1), dis(x1, y2), dis(x2, y1), dis(x2, y2)}) E;
  return 0;
}