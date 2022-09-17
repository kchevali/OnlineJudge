#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

using l = long long;
using vl = vector<l>;

l modPow(l a, l b, l m) {
  l tot = 1, num = a % m;
  while (b > 0) {
    if ((b & 1) == 1) tot = (tot * num) % m;
    b >>= 1;
    num = (num * num) % m;
  }
  return tot;
}

bool witnessPrimeTest(l n){
    if(n == 2 or n == 3) return true;
    if((n & 1) == 0) return false;

    l w[12] {0,0,0,0,0,0,0,0,0,0,0,0};
    if(n < 1'373'653) w[0] = 2, w[1] = 3;
    else if(n < 9'080'191) w[0] = 31, w[1] = 73;
    else if(n < 25'326'001) w[0] = 2, w[1] = 3, w[2] = 5;
    else if(n < 1'122'004'669'633) w[0] = 2, w[1] = 13, w[2] = 23, w[3]=1'662'803;
    // else if(n < 2'152'302'898'747) w[0] = 2, w[1] = 3, w[2] = 5, w[3]=7, w[4] = 11;
    // else w[0] = 2, w[1] = 3, w[2] = 5, w[3]=7, w[4] = 11, w[5] = 13, w[6] = 17, w[7] = 19, w[8] = 23, w[9] = 29, w[10] = 31, w[11] = 37;


    for (l a: w){
        if(a == 0) break;
        l m = 0, d = n - 1;
        bool matched = false;
        while((d & 1) == 0){
            m += 1;
            d >>= 1;
            l res = modPow(a, d, n);
            if (res == 1 || res == n - 1){
                matched = true;
                break;
            }
        }
        if (!matched) return false;
    }
    // cout << n << " " << m << " " << d << " -> " << modPow(a, d, n) << "\n";
    return true;
}

class Primes {
 public:
  vl primes;
  vector<bool> bs;

  // Upper | # of Primes
  //   1e8 | 6e6
  //   1e7 | 7e5
  //   1e6 | 8e4
  //   1e5 | 1e4
  //   1e4 | 1300

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

  // return a list of prime factors of N
  // e.g. N = 1000 => {2, 2, 2, 5, 5, 5}
  // use set instead of list if you don't want duplications
  vl primeFactor(l N) {
    vl factors;
    l i = 0, pf = primes[i];
    while (N != 1 && (pf * pf) <= N) {
      while (N % pf == 0) {
        N /= pf;
        factors.push_back(pf);
      }
      pf = primes[++i];
    }
    // special case: N is a prime
    if (N != 1) factors.push_back(N);
    return factors;
  }

  // return number of factors / prime factors / unique prime factors or freq of each prime factor
  vl pfCount(l N) {
    vl counts;
    l factorCount = 1, pfCount = 0, pfUniqueCount = 0;
    for (l i = 0, pf = primes[i]; N != 1 && (pf * pf) <= N; pf = primes[++i]) {
      l count = 0;
      while (N % pf == 0) {
        N /= pf;
        count++;
      }
      if (count > 0) {
        pfUniqueCount++;
        factorCount *= (1 + count);
        pfCount += count;
        counts.push_back(count);
      }
    }
    // special case: N is a prime
    if (N != 1) {
      factorCount *= 2;
      pfCount++;
      pfUniqueCount++;
      counts.push_back(1);
    }
    return counts;  // factorCount,pfUniqueCount,pfCount
  }
};

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    vector<l> primes;
    primes.push_back(2);
    for(l i = 3; i < 1e7; i+=2){
        if(witnessPrimeTest(i)) primes.push_back(i);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    std::chrono::steady_clock::time_point start_sieve = std::chrono::steady_clock::now();
    Primes p(1e7);
    std::chrono::steady_clock::time_point end_sieve = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end_sieve - start_sieve).count() << "[ms]" << std::endl;
    
    cout << "Same Size: " << (primes.size() == p.primes.size() ? "PASS" : "FAIL") << "\n";
    cout << "Est Count: " << primes.size() << "\n";
    cout << "Sieve Count: " << p.primes.size() << "\n";
}