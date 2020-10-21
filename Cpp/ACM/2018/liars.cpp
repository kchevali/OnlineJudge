#include "../../Template.cpp"
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, i;
  I n;
  vector<ll> v(n, ll());
  fpp(i, 0, n) { I v[i].F >> v[i].S; }
  fmm(i, 0, n + 1) {
    l x = 0;
    for (ll p : v) {
      x += (i >= p.F && i <= p.S);
    }
    if (x == i) {
      C i E;
      return 0;
    }
  }
  C - 1 E;
  return 0;
}