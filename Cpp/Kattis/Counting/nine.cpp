#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
typedef long long l;
#define MOD 1000000007LL

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l t, n, i, j;

  vector<l> pows(63);
  pows[0] = 9LL;
  fpp(i, 1, 64) { pows[i] = (pows[i - 1] * pows[i - 1]) % MOD; }

  cin >> t;
  fpp(i, 0, t) {
    cin >> n;
    l ans = 1LL;
    n--;
    for (j = 0; n != 0; j++) {
      if ((n & 1) != 0) ans = (ans * pows[j]) % MOD;
      n >>= 1;
    }
    cout << ((ans * 8LL) % MOD) << endl;
  }
}
