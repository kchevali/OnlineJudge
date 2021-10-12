#include <bits/stdc++.h>
using namespace std;
typedef long long l;

double roll(l n, l k){
  if(k == 0) return 0;
  double total = 0;
  double next = roll(n, k - 1);
  for(l i = 1; i <= n; i++){
    total += max((double)i, next);
  }
  return total / n;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, k;
  cin >> n >> k;
  cout << fixed << setprecision(13) << roll(n, k) << "\n";

}
