#include <bits/stdc++.h>
#define C cout <<
#define E << "\n"
#define fpp(i, a, b) for (i = a; i < b; i++)
#define v(t) vector<t>
using namespace std;
typedef long long l;
typedef v(l) vl;

l LIS(string &arr) {
  vl dp(arr.length(), 0);
  l i, j, mx = 0;
  fpp(i, 0, arr.length()) {
    fpp(j, i + 1, arr.length()) if (arr[j] > arr[i]) dp[j] =
        max(dp[j], dp[i] + 1);
    mx = max(mx, dp[i]);
  }
  return mx + 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  C(26 - LIS(s)) E;
}
