#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  for(l i = 0; i < n; i++){
    l m, p1, p2;
    cin >> m >> p1 >> p2;
    for(l j = 2; j < m; j++){
      l x;
      cin >> x;
      if((p2 <= p1 || p2 >= x) && x > p1)cout << (j) << "\n";
      p1 = p2;
      p2 = x;
    }
  }
}
