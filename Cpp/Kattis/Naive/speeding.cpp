#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  l v = 0, prevT, prevD;
  cin >> prevT >> prevD;
  for(l i = 1 ; i < n; i++){
    l t, d;
    cin >> t >> d;
    v = max((d-prevD) / (t-prevT), v);
    prevD = d, prevT = t;
  }
  cout << v << '\n';
}
