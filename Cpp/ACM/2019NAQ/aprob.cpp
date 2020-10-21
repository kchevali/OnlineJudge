#include <bits/stdc++.h>
using namespace std;
typedef long long l;

const l N = 101;
l n;
double p[N];

double f(double a, double n) { return pow(a, a / n); }

// double g(l i, l j, l k) {
//   if (j == 0) return 0.0;
//   if (i == k) return f(j, k);
//   return nums[i] * g(i + 1, j + 1, k) + (1 - nums[i]) * g(i + 1, j, k);
// }

double g(l acc, l sub) {
  if (acc == 0) return 0.0;

  double r = 1, w = 1;
  for (l i = 0; i < acc; i++) {
    r *= p[i];
  }
  for (l i = acc; i < n; i++) {
    w *= (1 - p[i]);
  }
  cout << "r: " << r << " w: " << w << "\n";
  return r * f(acc, sub) + w * f(n - acc, sub);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // cin >> n;

  // for (l i = 0; i < n; i++) {
  //   cin >> nums[i];
  //   nums[i] /= 100.0;
  // }
  // sort(nums, nums + n, greater<double>());
  // double mx = 0;
  // for (l i = 0; i < n; i++) {
  //   cout << nums[i] << "\n";
  //   for (l j = 0; j < n; j++) {
  //     mx = max(mx, g(0, j, i));
  //   }
  // }
  // cout << mx << "\n";

  // WHATS the chance of getting 1 paper submitted at 10%
  p[0] = 0.10;
  cout << g(1, 1) << "\n";
}
