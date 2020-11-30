#include "../all.cpp"
// Prime Number
// Here are some useful methods that dealing with primes numbers.
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

  // Also known as "Euler's totient function"
  // Counts the positive integers up to a given integer n that are relatively
  // prime to n
  // It is the number of integers k in the range 1 ≤ k ≤ n for which
  // the greatest common divisor gcd(n, k) is equal to 1
  l EulerPhi(l N) {
    l i = 0;
    l pf = primes[i], ans = N;
    while (N != 1 && (pf * pf) <= N) {
      if (N % pf == 0) ans -= ans / pf;
      while (N % pf == 0) N /= pf;
      pf = primes[++i];
    }
    if (N != 1) ans -= ans / N;
    return ans;
  }
};

l gcd(l a, l b) { return b == 0 ? a : gcd(b, a % b); }

// fast way of getting a sum range of the fib numbers
// need to construct the fib sequence first
// input index range [a,b) - exclusive b
l fib[0];
l fibSum(l a, l b) { return fib[b + 1] - fib[a + 1]; }

// Modulo
// IMPORTS:#define count __builtin_popcountll #define lead __builtin_clzll
l modAdd(l a, l b, l m) { return ((a % m) + (b % m)) % m; }
l modMul(l a, l b, l m) { return ((a % m) * (b % m)) % m; }
l modDiv(l a, l b, l m) { return ((a % m) / (b % m)) % m; }
l modPow(l a, l b, l m) {
  l tot = 1, num = a % m;
  while (b > 0) {
    if ((b & 1) == 1) tot = (tot * num) % m;
    b >>= 1;
    num = (num * num) % m;
  }
  return tot;
}

// solve Linear Equations
class LinearEquations {
 public:
  static const l length = 10;

  double a[length][length];
  double sol[length];

  // flag == 0 for No solution
  // flag == 1 for One Solution
  // else for infinite solution
  l gaussJordanElimination(l n) {
    // Performing elementary operations
    l flag = 1;
    for (l i = 0; i < n; i++) {
      if (a[i][i] == 0) {
        l c = 1;
        while (i + c < n && a[i + c][i] == 0) c++;
        if (i + c == n) {
          flag = 0;
          break;
        }
        for (l j = i, k = 0; k <= n; k++) swap(a[j][k], a[j + c][k]);
      }

      // Form Diagnoal
      for (l j = 0; j < n; j++) {
        if (i != j) {
          double pro = a[j][i] / a[i][i];
          for (l k = 0; k <= n; k++) a[j][k] -= a[i][k] * pro;
        }
      }
    }

    if (flag == 0) {
      for (l i = 0; i < n; i++) {
        double sum = 0;
        for (l j = 0; j < n; j++) sum += a[i][j];
        if (sum == a[i][n]) flag = 2;
      }
    }
    for (l i = 0; i < n; i++) sol[i] = a[i][n] / a[i][i];
    return flag;
  }

  double* operator[](l i) { return a[i]; }
};

// 2^3 = 2^1 * 2^2

/*
//LOOK AT SOLVING CONGRUENCE IN NUMBER THEORY
Mod Rules
// a ≡ b (mod m) -> a % m == b % m
(a ≡ b (mod m) if (m % (a-b) == 0)
a = b % m -> b = mx + a (for all int x)
3 = b % 4 -> b = 4x + 3


*/

int main() {
  l nums[]{1, 3, 100, 71, 47, 97};
  Prime primes = Prime(1000);

  cout << "\nIs Prime:\n";
  for (l num : nums) {
    cout << num << ": " << (primes.isPrime(num) ? "YES" : "NO") << "\n";
  }

  l num = 100;
  cout << "\nPrime Factors of: " << num << "\n";
  vl primeFactors = primes.primeFactor(num);
  for (l pf : primeFactors) cout << pf << " ";
  cout << "\nPrime Factor Count:" << primes.primeFactorCount(num) << "\n";

  cout << "Relative Primes Count for: " << num << " is " << primes.EulerPhi(num) << "\n";

  l a = 2 * 3 * 3 * 5, b = 3 * 5 * 7;
  cout << "\nGCD of " << a << " & " << b << " is " << gcd(a, b) << "\n";

  l x = 105, y = 1024, m = 1000;
  cout << "\n" << x << " ^ " << y << " MOD " << m << " = " << modPow(x, y, m) << "\n";

  cout << "\nSolve Linear Equation\nx + y = 10\n2x + 3y = 0\n";
  LinearEquations eq = LinearEquations();
  const l length = 2;
  l values[length][length + 1]{{1, 1, 10}, {2, 3, 0}};

  for (l i = 0; i < length; i++) {
    for (l j = 0; j < length + 1; j++) {
      eq[i][j] = values[i][j];
    }
  }

  l status = eq.gaussJordanElimination(length);
  cout << "Number of Solutions: " << (status == 1 ? "ONE" : (status == 0 ? "NONE" : "INFINITE")) << "\n";

  if (status == 1) {
    cout << "Solution:\n";
    for (l i = 0; i < length; i++) {
      cout << eq.sol[i] << " ";
    }
    cout << "\n";
  }
}