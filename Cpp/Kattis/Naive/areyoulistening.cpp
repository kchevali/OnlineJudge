#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l x, y, n;
  scanf("%lld%lld%lld", &x, &y, &n);
  l pts[n];
  for (l i = 0; i < n; i++) {
    l a, b, r;
    scanf("%lld%lld%lld", &a, &b, &r);
    pts[i] = (l)(sqrt((a - x) * (a - x) + (b - y) * (b - y)) - r);
  }
  sort(pts, pts + n);
  printf("%lld\n", max(0LL, pts[2]));
}
