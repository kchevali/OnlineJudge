#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l a, b, c, d;
  cin >> a >> b >> c >>d;

  cout << ((a>=c+2) && (b>=d+2)) << "\n";
}
