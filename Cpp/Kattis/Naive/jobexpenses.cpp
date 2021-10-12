#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, t = 0;
  cin >> n;
  for(l i = 0; i < n; i++){
    l x;
    cin >> x;
    t += min(x,0LL);
  }
  cout << -t << "\n";
}
