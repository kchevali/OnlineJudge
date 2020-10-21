#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
  double n, x, v;
  cin >> n >> x >> v;

  double y_v = 0;
  for (int i = 0; i < n; i++) {
    double a, b, c;
    cin >> a >> b >> c;
    y_v += (b - a) / x * c;
  }
  double x_v = sqrt(v * v - y_v * y_v);
  if (y_v * y_v > v * v || x_v * 2 < v) {
    cout << "Too hard" << endl;
  } else {
    cout << fixed << setprecision(3) << x / x_v << endl;
  }
  return 0;
}

/*



*/