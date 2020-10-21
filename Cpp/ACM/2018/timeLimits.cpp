#include "../../Template.cpp"
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m, i, x, mx = -1;
  I n >> m;
  fpp(i, 0, n) {
    I x;
    if (x > mx) mx = x;
  }
  C ceil(mx * m / 1000.0) E;
}