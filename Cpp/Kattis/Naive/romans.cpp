#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  double x;
  cin >> x;

  cout << (l)round(x * 1000.0 * 5280.0 / 4854.0) << '\n';
}
