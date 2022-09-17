#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  double score = 0, newScore = 0;
  for( l i = 0; i < n; i++){
    l x;
    cin >> x;
    double s = x * pow(0.8, i);
    score +=  s;
    newScore += i * x * pow(0.8, i-1) + (n - i - 1) * s;
  }
  cout << fixed << setprecision(8) << (score / 5) << "\n" << (newScore / (5 * n)) << "\n";
}
