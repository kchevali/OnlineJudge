#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
typedef long long l;
typedef vector<l> vl;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m, i, x, t = 1;
  while (cin >> n) {
    cout << "Case " << (t++) << ":\n";
    vl nums = vl(n);
    for (auto& p : nums) cin >> p;
    sort(nums.begin(), nums.end());
    cin >> m;
    fpp(i, 0, m) {
      cin >> x;
      l j = 0, k = n - 1, best = abs(nums[j] + nums[k] - x),
        sum = nums[j] + nums[k];
      while (j < k && best > 0) {
        if (abs(nums[j] + nums[k] - x) < best) {
          best = abs(nums[j] + nums[k] - x);
          sum = nums[j] + nums[k];
        }
        if (nums[k] + nums[j] > x)
          k--;
        else
          j++;
      }
      cout << "Closest sum to " << x << " is " << sum << ".\n";
    }
  }
}