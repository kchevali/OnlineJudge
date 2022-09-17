#include <bits/stdc++.h>
using namespace std;
typedef long long l;

inline double dist(double a, double b, double c, double d){
  return sqrt((a-c)*(a-c) + (b-d)*(b-d));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  double a, b, c, d, e, f, g, h;
  cin >> a >> b >> c >> d >> e >> f >> g >> h;
  cout << fixed << setprecision(8) << max(dist(a,b,c,d), dist(e,f,g,h)) << "\n";
}
