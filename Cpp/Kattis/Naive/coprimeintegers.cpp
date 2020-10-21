#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
using namespace std;
typedef long long l;
typedef double o;
typedef v(l) vl;
typedef v(bool) vb;

l a, b, c, d, ps;

inline l numPairs(l k) { return (b / k - (a - 1) / k) * (d / k - (c - 1) / k); }

vl primes = vl();
vb bs;

void sieve(l upper) {
  l size = upper + 1, i;
  bs = vb(size, true);
  bs[0] = bs[1] = false;
  fpp(i, 2, size) if (bs[i]) {
    for (l j = i * i; j < size; j += i) bs[j] = false;
    primes.PB(i);
  }
  ps = primes.size();
}

l MAX = 10000000LL;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> a >> b >> c >> d;
  l counter = (b - a + 1) * (d - c + 1), i, mx = max(b, d) + 1, x, sign, index;
  sieve(10000000LL);

  l k = 0;
  vl q = vl(7000);
  q[k++] = -MAX - 1;  // x, sign, index//sign*(index + x*MAX)
  while (k > 0) {
    l num = q[--k];
    sign = num > 0 ? 1 : -1;
    num = sign * num;
    x = num / MAX;
    index = (num % MAX) - 1;
    fpp(i, index, ps) {
      l xp = x * primes[i];
      if (xp >= mx) break;
      q[k++] = sign * (i + 2 + x * MAX);
      counter += numPairs(x = xp) * sign;
      sign *= -1;
    }
  }
  C counter E;
  return 0;
}
