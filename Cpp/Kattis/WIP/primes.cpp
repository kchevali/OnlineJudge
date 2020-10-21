#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;
const l N = 10;
// l pows[N][35];
l length[N], primes[N], digits[N], nums[N], sol[1000];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l p;
  while (scanf("%lld", &p) && p > 0) {
    l a, b;
    for (l i = 0; i < p; i++) scanf("%lld", &primes[i]);
    scanf("%lld%lld", &a, &b);
    memset(digits, 0, sizeof(digits));

    for (l i = 0; i < p; i++) {
      length[i] = (l)(log(b) / log(primes[i]));
      nums[i] = 1;
      // cout << "PRIME: " << primes[i] << " " << length[i] << "\n";
    }
    l total = 1, index = 0, solIndex = 0;
    l debug = 0;
    if (total >= a) sol[solIndex++] = total;
    // cout << "T:" << total << "\n";
    while (index < p) {
      l inc = 1;
      index = 0;
      while (inc > 0 && index < p) {
        if (digits[index]++ < length[index]) {
          inc = 0;
          nums[index] *= primes[index];
          total *= primes[index];
          if (debug++ == 100) return 0;

          if (total <= b) {
            if (total >= a) sol[solIndex++] = total;

            // if (total > 0) {// || (debug++) % 1 == 0
            cout << "T:" << total << "\tD:";
            for (l j = 0; j < p; j++) cout << digits[j] << "\t";
            cout << "\n";
            // }
          } else {
            inc = 1;
          }
        } else {
          total /= nums[index];
          digits[index] = 0;
          nums[index++] = 1;
        }
      }
    }
    if (solIndex == 0) {
      printf("none\n");
      continue;
    }
    sort(sol, sol + solIndex);
    printf("%lld", sol[0]);
    for (l i = 1; i < solIndex; i++) printf(",%lld", sol[i]);
    printf("\n");
  }
}

/*
10
2 3 5 7 11 13 17 19 23 29
1 1000000000
1 2147483647
*/