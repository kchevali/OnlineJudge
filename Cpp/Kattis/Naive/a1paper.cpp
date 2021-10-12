#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  n--;

  l num = 1;
  double total = 0, width = pow(2.0, - 5.0 / 4.0), length = pow(2.0, - 3.0 / 4.0);
  for(l i = 0; i < n && num > 0; i++){

    total += length * num;
    swap(length, width);
    width /= 2;
    
    l x;
    cin >> x;    
    num = 2 * num - x;
    
  }
  if(num > 0)cout << "impossible\n";
  else cout << fixed << setprecision(12) << total << "\n";

}