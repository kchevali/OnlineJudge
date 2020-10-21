#include "../all.cpp"

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
  fpp(i, 0, n) {
    l x, y;
    cin >> x >> y;
    pts[i].first = x * r + y;
    pts[i].second = y - x * r;
    // cout << "Found: " << pts[i].first << " " << pts[i].second << "\n";
  }
  sort(pts.begin(), pts.end());

  vl array = vl(n);
  fpp(i, 0, n) array[i] = pts[i].second;

  // arr(array);

  cout << LISFaster(array) << "\n";
}
/*

5 1 10 10
8 8
5 1
4 6
4 7
7 9


*/
