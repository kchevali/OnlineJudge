#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l t;
  cin >> t;
  while(t--){
    l n;
    cin >> n;
    l total = 0;
    for(l i = 0; i < n; i++){
      l x;
      cin >> x;
      total += x - (i != 0);
    }
    cout << total << "\n";
  }
}
