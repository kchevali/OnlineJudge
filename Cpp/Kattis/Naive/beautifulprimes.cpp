#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l nums[1010], primes[3] = {5, 7, 11};
  double prod = nums[1] = 5;

  for (l i = 2; i <= 1000; i++) {
    for (l p : primes) {
      double num = prod * p;
      if (num >= 10) {
        nums[i] = p;
        prod = num / 10;
        break;
      }
    }
  }

  l cases, n;
  scanf("%lld", &cases);
  for (l i = 0; i < cases; i++) {
    scanf("%lld", &n);
    for (l j = 1; j <= n; j++) printf("%lld ", nums[j]);
    printf("\n");
  }
}
