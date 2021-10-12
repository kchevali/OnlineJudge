#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  double a,b,c,d;
  cin >> a >> b >> c >> d;
  double s = (a+b+c+d)/2;
  cout << fixed << setprecision(10) << sqrt((s-a)*(s-b)*(s-c)*(s-d)) << "\n";
}
