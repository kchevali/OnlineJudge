#include "../all.cpp"

// Global Variables
//============================
const l N = 100;
l dp[N], nums[N], p[N], t[N];

// Dynamic Programming
// Longest Increasing Subsequence (LIS)
// Finding the length of longest increasing subsequence or the subsequence
// itself. e.g. given a list {3, 8, 4, 6, 2, 9} the length of LIS is 4, which is
// {3, 4, 6, 9}

// const l N = 100;
// l dp[N], nums[N];
// Complexity: O(n^2) with indicies?
l LIS(l n) {
  memset(dp, 0, sizeof(dp));
  l mx = 0;
  for (l i = 0; i < n; i++) {
    for (l j = i + 1; j < n; j++)
      if (nums[j] > nums[i]) dp[j] = max(dp[j], dp[i] + 1);
    mx = max(mx, dp[i]);
  }
  return mx + 1;
}

// const l N = 100;
// l nums[N], p[N], t[N];
// Complexity: O(nlogn) with indices
vector<l> LIS_FAST(l n) {
  memset(p, -1, sizeof(l) * n);
  memset(t, 0, sizeof(l) * n);

  l lis = 1;
  for (l i = 1; i < n; i++) {
    if (nums[i] <= nums[t[0]]) {
      t[0] = i;
    } else if (nums[i] > nums[t[lis - 1]]) {
      p[i] = t[lis - 1];
      t[lis++] = i;
    } else {
      l a = -1, b = lis - 1;
      while (b - a > 1) {
        l m = a + (b - a) / 2;
        if (nums[t[m]] >= nums[i])
          b = m;
        else
          a = m;
      }
      p[i] = t[b - 1];
      t[b] = i;
    }
  }

  vector<l> ans;
  for (l i = t[lis - 1]; i >= 0; i = p[i]) {
    ans.push_back(i);
  }
  reverse(ans.begin(), ans.end());

  return ans;
}

int main() {
  l n;
  scanf("%lld", &n);
  for (l i = 0; i < n; i++) scanf("%lld", nums + i);

  vl x = LIS_FAST(n);
  cout << "Length: " << x.size() << "\n";
  for (const auto& y : x) cout << y << " ";
  cout << "\n";

  // cout << "Length: " << LIS(n) << endl;
}
/*
13
1 10 5 6 7 8 9 2 3 4 5 6 7
Output:7
*/
