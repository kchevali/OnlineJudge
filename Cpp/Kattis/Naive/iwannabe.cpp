#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, k;
  cin >> n >> k;

  pair<l,l> a[3][n];
  for(l i = 0; i < n; i++){
    for(l j = 0; j < 3; j++){
      cin >> a[j][i].first;
      a[j][i].second = i;
    }
  }
  for(l i = 0; i < 3; i++){
    sort(a[i], a[i] + n, greater<pair<l,l>>());
  }

  bool inUse[n];
  memset(inUse, 0, sizeof(inUse));

  l total = 0;
  for(l i = 0; i < 3; i++){
    for(l j = 0; j < k; j++){
      auto [_, idx] = a[i][j];
      if(!inUse[idx]){
        inUse[idx] = true;
        total++;
      }
    }
  }
  cout << total << "\n";

}
