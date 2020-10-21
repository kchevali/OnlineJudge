#include <bits/stdc++.h>
using namespace std;
typedef long long l;

l nums[7];

int main() {
  l n, x;
  memset(nums, -1, sizeof nums);
  scanf("%lld", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &x);
    if (nums[x] == -1)
      nums[x] = i;
    else
      nums[x] = -2;
  }
  for (int i = 7; i-- > 1;) {
    if (nums[i] >= 0) {
      printf("%lld\n", nums[i] + 1);
      return 0;
    }
  }
  printf("none\n");
}