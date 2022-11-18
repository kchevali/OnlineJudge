#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  double px, py, a = 0;
  cin >> px >> py;
  for(l i = 1; i < n; i++){
    double x, y;
    cin >> x >> y;
    a += (y + py) * (x - px)  / 2.0;
    px = x, py = y;
  }
  cout << fixed << setprecision(8) << (a / 1000) << "\n";
}
