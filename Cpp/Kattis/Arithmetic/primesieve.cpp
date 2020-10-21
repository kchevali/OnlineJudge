#include <bits/stdc++.h>
using namespace std;
typedef long long l;
const l N = 1e8 + 10;
bitset<N> bs;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, q, x, primeCount = 0;
  scanf("%lld%lld", &n, &q);
  n++;
  bs.set();
  bs.reset(0);
  bs.reset(1);
  for (l i = 2; i < n; i++)
    if (bs[i]) {
      primeCount++;
      for (l j = i * i; j < n; j += i) bs.reset(j);
    }
  printf("%lld\n", primeCount);
  for (l i = 0; i < q; i++) {
    scanf("%lld", &x);
    printf("%d\n", (int)bs[x]);
  }
}
