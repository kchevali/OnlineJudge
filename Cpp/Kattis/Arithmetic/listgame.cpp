#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
typedef long long l;
typedef vector<bool> vb;
typedef vector<l> vl;

#define fmm(i, a, b) for (i = b; i-- > a;)

vl primes = vl();
vb bs;

void sieve(l upper) {
  l size = upper + 1, i;
  bs = vb(size, true);
  bs[0] = bs[1] = false;
  fpp(i, 2, size) if (bs[i]) {
    for (l j = i * i; j < size; j += i) bs[j] = false;
    primes.emplace_back(i);
  }
}

l primeFactor(l N) {
  l factors = 0;
  l i = 0, pf = primes[i];
  while (N != 1 && (pf * pf) <= N) {
    while (N % pf == 0) {
      N /= pf;
      factors++;
    }
    pf = primes[++i];
  }
  // special case: N is a prime
  if (N != 1) factors++;
  return factors;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  sieve(10000000LL);
  l i;
  cout << primeFactor(n) << "\n";
}