#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l s, t, n;
  cin >> s >> t >> n;

  l a[3][n], x;
  cin >> x;
  s += x; 

  for(l j = 0; j < 3; j++){
    for(l i = 0; i < n; i++){
      cin >> a[j][i];
    }
  }

  for(l i = 0; i < n; i++){
    s = ((s / a[2][i]) + (s % a[2][i] != 0)) * a[2][i] + a[1][i] + a[0][i];
  }
  // cout << s << " " << t << "\n";
  cout << (s <= t ? "yes" : "no") << "\n";

}
