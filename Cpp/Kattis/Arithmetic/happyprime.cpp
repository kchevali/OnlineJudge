#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

class Primes {
 public:
  vl primes = vl();
  vector<bool> bs;

  // SIEVE
  // generate all prime number that is less than or equal to upper
  // pretty fast if upper <= 10^7
  // call this method only once in main method, use 10^7 is enough for most of
  // the cases a lot of following methods need prime list
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

  // return true if the number N is a prime number
  //***IMPORTANT*** only works if N <= (the largest prime in the prime list)^2
  bool isPrime(l N) {
    if (N < bs.size()) return bs[N];
    for (l p : primes)
      if (N % p == 0) return false;
    return true;
  }
};

bool isHappy(l num) {
  for (l i = 0; i < 6 && num != 1; i++) {
    l next = 0;
    while (num > 0) {
      l x = num % 10;
      next += x * x;
      num /= 10;
    }
    num = next;
  }
  return num == 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l p;
  scanf("%lld", &p);
  Primes primes = Primes(10000);
  for (l i = 0; i < p; i++) {
    l a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld %lld %s\n", a, b, primes.isPrime(b) && isHappy(b) ? "YES" : "NO");
  }
}
