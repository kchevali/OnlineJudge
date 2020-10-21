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

vl primes{2, 3, 5, 7, 11, 13, 17, 19};
vl reg;

bool increment(l index) {
  if (index == 8) return false;
  if (++reg[index] == primes[index]) {
    reg[index] = 0;
    return increment(index + 1);
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  reg = vl(8);
  l i, count = 0;
  fpp(i, 0, 8) cin >> reg[i];
  while (increment(0)) count++;
  C count E;
}
