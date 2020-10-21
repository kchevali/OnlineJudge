#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<pair<l, l>> vll;

l LISFaster(vl array) {
  vl dp(array.size());
  dp[0] = array[0];
  l ans = 1;
  for (l i = 1; i < array.size(); i++) {
    l low = 0, high = ans - 1;
    while (low <= high) {
      l mid = (low + high) / 2;
      if (dp[mid] <= array[i])
        low = mid + 1;
      else
        high = mid - 1;
    }
    dp[low] = array[i];
    ans = max(ans, low + 1);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, r, w, h, i;
  cin >> n >> r >> w >> h;

  vll pts(n);
  for (int i = 0; i < n; i++) {
    l x, y;
    cin >> x >> y;
    pts[i].first = x * r + y;
    pts[i].second = y - x * r;
  }
  sort(pts.begin(), pts.end());

  vl array = vl(n);
  for (int i = 0; i < n; i++) array[i] = pts[i].second;

  cout << LISFaster(array) << "\n";
}
