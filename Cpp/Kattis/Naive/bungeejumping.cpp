#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
#define gc getchar_unlocked

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  double rope, len, h, weight;
  cin >> rope >> len >> h >> weight;
  while (rope > 0 || len > 0 || h > 0 || weight > 0) {
    double remaining = max(0.0, h - len), tension = remaining * rope,
           gravity = weight * 9.81;
    double v = sqrt(2 * 9.81 * h - (rope * remaining * remaining) / weight);
    cout << (v > 10 ? "Killed by the impact."
                    : (v >= 0 ? "James Bond survives." : "Stuck in the air."))
         << "\n";
    cin >> rope >> len >> h >> weight;
  }
}
