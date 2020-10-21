#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, x;
  scanf("%lld%lld", &n, &x);
  l nums[n];
  for (l i = 0; i < n; i++) scanf("%lld", nums + i);
  sort(nums, nums + n);
  l i = 1;
  while (i < n && nums[i] + nums[i - 1] <= x) i++;
  printf("%lld\n", max(1LL, i));  //|| nums[0] + nums[1] >= x
}
