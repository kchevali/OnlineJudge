#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

class Primes {
 public:
  vl primes;
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

double getF(Primes& p) {
  double total = 0, mult = 1;
  for (l prime : p.primes) {
    total += (prime - 1) / mult;
    mult *= prime;
    cout << mult << "\n";
  }
  return total;
}

double next(double f) { return floor(f) * (f - floor(f) + 1); }

int main() {
  Primes p(89);

  double f = getF(p);
  for (l i = 0; i < p.primes.size(); i++) {
    l prime = (l)floor(f);
    if (prime != p.primes[i]) {
      cout << "Correct: " << (100.0 * i / p.primes.size()) << "% \n";
      exit(0);
    }
    f = next(f);
  }
  cout << "PASS ALL\n";
}
