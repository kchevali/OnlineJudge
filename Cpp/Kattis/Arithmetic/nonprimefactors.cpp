#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

const l N = 2e6 + 10;
l dp[N];

class Primes {
 public:
  vl primes = vl();
  vector<bool> bs;

  Primes(l upper) {
    l size = upper + 1, i;
    bs = vector<bool>(size, true);
    bs[0] = bs[1] = false;
    for (l i = 2; i < size; i++)
      if (bs[i]) {
        for (l j = i * i; j < size; j += i) bs[j] = false;
        primes.push_back(i);
      }
  }
  l pfCount(l N) {
    l factorCount = 1, pfUniqueCount = 0;
    for (l i = 0, pf = primes[i]; N != 1 && (pf * pf) <= N; pf = primes[++i]) {
      l count = 0;
      while (N % pf == 0) {
        N /= pf;
        count++;
      }
      if (count > 0) {
        pfUniqueCount++;
        factorCount *= (1 + count);
      }
    }
    // special case: N is a prime
    if (N != 1) {
      factorCount *= 2;
      pfUniqueCount++;
    }
    return factorCount - pfUniqueCount;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l q;
  scanf("%lld", &q);
  Primes p = Primes(2 * 1e6);
  memset(dp, -1, sizeof(dp));
  for (l i = 0; i < q; i++) {
    l x;
    scanf("%lld", &x);
    if (dp[x] == -1) {
      dp[x] = p.pfCount(x);
    }
    printf("%lld\n", dp[x]);
  }
}