#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l x[3];
  while (true) {
    for (l i = 0; i < 3; i++) cin >> x[i];
    if (x[0] == 0) break;
    sort(x, x + 3);
    cout << (x[0] * x[0] + x[1] * x[1] == x[2] * x[2] ? "right\n" : "wrong\n");
  }
}
