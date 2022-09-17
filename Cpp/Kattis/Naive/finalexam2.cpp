#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  char prev = 0;
  l total = 0;
  for(l i = 0 ; i < n; i++){
    char x;
    cin >> x;
    total += (x == prev);
    prev = x;
  }
  cout << total << "\n";
}
