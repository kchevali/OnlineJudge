#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

const l R = 14 + 1, C = 2000 + 5, mod = 1e9 + 7;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l pows3[C], pows2[C];
  pows3[0] = pows2[0] = 1;
  for (l i = 1; i < C; i++) {
    pows3[i] = (pows3[i - 1] * 3) % mod;
    pows2[i] = (pows2[i - 1] * 2) % mod;
  }

  l n;
  cin >> n;
  for (l i = 0; i < n; i++) {
    l r, c;
    cin >> r >> c;
    l total = (((pows3[c] * pows2[c]) % mod) * pows3[r]) % mod;
    for (l i = 1; i < r; i++) {
      total = (total * pows2[c]) % mod;
    }
    printf("%lld\n", total);
  }
}

// 3*3*2*1