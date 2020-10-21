#include "../../all.cpp"

const l N = 1e6 + 1;
vl primes;
vb bs(N, true);

void sieve(l x) {
  bs[0] = bs[1] = false;
  l size = x + 1, i, j;
  fpp(i, 2, size) if (bs[i]) {
    for (j = i * i; j < size; j += i) bs[j] = false;
    primes.PB(i);
  }
}

// return true if the number n is a prime number
//***IMPORTAnT*** only works if n <= (the largest prime in the prime list)^2
bool isPrime(l n) {
  if (n < bs.size()) return bs[n];
  for (l p : primes)
    if (n % p == 0) return false;
  return true;
}
l step(l n) {
  if (n < 4) return 0;
  for (auto a : primes) {
    l b = n - a;
    if (isPrime(b) && !((b - a) & 1)) return step(b - a) + 1;
  }
  return 0;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  sieve(n);
  C step(n) E;
}