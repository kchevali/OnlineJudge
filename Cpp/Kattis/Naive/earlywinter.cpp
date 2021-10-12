#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, x;
  cin >> n >> x;
  for(l i = 0; i < n; i++){
    l y;
    cin >> y;
    if(y <= x){
      cout << "It hadn't snowed this early in " << i << " years!\n";
      return 0;
    }
  }
  cout << "It had never snowed this early!\n";
}
