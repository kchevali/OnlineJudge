#include <bits/stdc++.h>
using namespace std;
typedef long long l;

l getPosition(l num, l n) {
  if (n == 1) return num;

  l bit = 1LL << (n - 1);
  l val = num >> (n - 1);
  l prev = getPosition((bit - 1) & num, n - 1);
  return val == 0 ? prev : val * bit + (bit - prev - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, a, b;
  string x, y;

  cin >> n >> x >> y;
  a = bitset<64>(x).to_ullong();
  b = bitset<64>(y).to_ullong();
  printf("%lld\n", getPosition(b, n) - getPosition(a, n) - 1);
}
