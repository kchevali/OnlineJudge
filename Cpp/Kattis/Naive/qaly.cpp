#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  double total = 0;
  for(l i = 0; i < n; i++){
    double a, b;
    cin >> a >> b;
    total += a*b;
  }
  cout << total;
}
