#include "../../all.cpp"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, a = 0, i;
  string x, y;
  cin >> n >> x >> y;
  l len = x.length(), m = len - n;
  fpp(i, 0, len) {
    if (x[i] == y[i]) {
      if (n > 0) {
        n--;
        a++;
      }
    } else if (m > 0) {
      m--;
      a++;
    }
  }

  cout << a << endl;
}
