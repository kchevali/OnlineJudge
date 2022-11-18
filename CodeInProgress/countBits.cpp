#include "../../all.cpp"

l k;

l c(l b, l j) {
  if (b == 0 && j == 0) return 1;
  if (b == 0) return 0;
  l mx = (1LL << b), c = 0;
  for (l i = j; i < mx; i += k) c++;
  return c;
}

l f(l b, l j) {
  if (b == 0) return 0;
  l mx = (1LL << b), c = 0;
  for (l i = j; i < mx; i += k) c += count(i);
  return c;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  k = 10;
  l b = 5;
  l i, j;
  fpp(i, 0, b + 1) {
    fpp(j, 0, k + 1) { C c(i, j) _ ""; }
    C "" E;
  }
  C "" E;
  fpp(i, 0, b + 1) {
    fpp(j, 0, k + 1) { C f(i, j) _ ""; }
    C "" E;
  }
  C "ANS:" _(f(b, 0) % 1000000009LL) E;
}