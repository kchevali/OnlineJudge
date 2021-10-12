#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m;
  cin >> n >> m;

  l bits[m];
  for(l i = 0; i < m; i++){
    l x, y;
    cin >> x >> y;
    bits[i] = (1 << (x - 1)) | (1 << (y-1));
  }

  l total = 0;
  for(l i = 0, len = (1 << n); i < len; i++){
    bool match = false;
    for(l b: bits){
      if((b & i) == b){
        match = true;
        break;
      }
    }
    total += !match;
  }
  cout << total << "\n";
}
