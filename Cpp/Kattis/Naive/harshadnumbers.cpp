#include <bits/stdc++.h>
using namespace std;
typedef long long l;

bool pass(l x){
  l sum = 0, c = x;
  while(x > 0){
    sum += x % 10;
    x /= 10;
  }
  return c % sum == 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n;
  cin >> n;
  while(!pass(n)){
    n++;
  }
  cout << n << "\n";
}
