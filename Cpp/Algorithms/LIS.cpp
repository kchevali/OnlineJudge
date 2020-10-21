#include "../all.cpp"

// Dynamic Programming
// Longest Increasing Subsequence (LIS)
// Finding the length of longest increasing subsequence or the subsequence
// itself. e.g. given a list {3, 8, 4, 6, 2, 9} the length of LIS is 4, which is
// {3, 4, 6, 9} There are two approaches, the first one is slower, O(n2) time
// complexity.

l LIS(vl &arr) {
  vl dp(arr.size(), 0);
  l i, j, mx = 0;
  fpp(i, 0, arr.size()) {
    fpp(j, i + 1, arr.size()) if (arr[j] > arr[i]) dp[j] =
        max(dp[j], dp[i] + 1);
    mx = max(mx, dp[i]);
  }
  return mx + 1;
}

// l binary_search(vl v, l data) {
//   auto it = lower_bound(v.begin(), v.end(), data);
//   return it == v.end() || *it != data ? -1 : distance(v.begin(), it);
// }

// LIS with O(n lg n)
#define MID(x, y) x + (y - x) / 2
l LIS2(vl &v) {
  vl dp = vl(v.size(), 0);
  dp[0] = v[0];
  l x = 1, i;
  fpp(i, 1, v.size()) {
    l a = 0, b = x - 1;
    while (a <= b) {
      l m = MID(a, b);
      if (dp[m] < v[i])
        a = m + 1;
      else
        b = m - 1;
    }
    dp[a] = v[i];
    x = max(x, a + 1);
  }
  return x;
}

// Same approach, an alternative way to write it following.(This only return the
// length of the LIS)

l LISFaster(vo array) {
  vo dp(array.size());
  dp[0] = array[0];
  l ans = 1;
  for (l i = 1; i < array.size(); i++) {
    l low = 0, high = ans - 1;
    while (low <= high) {
      l mid = (low + high) / 2;
      if (dp[mid] < array[i])
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
  vl v = {1, 10, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7};
  cout << LIS2(v) << endl;
  return 0;
}
