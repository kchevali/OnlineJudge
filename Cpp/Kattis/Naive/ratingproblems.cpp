#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, k;
  cin >> n >> k;
  l t = 0;
  for(l i = 0; i < k; i++){
    l x;
    cin >> x;
    t += x;
  } 
  cout << ((double)(t - 3 * (n - k)) / n) << " " << ((double)(t + 3 * (n - k)) / n) << "\n";
}
