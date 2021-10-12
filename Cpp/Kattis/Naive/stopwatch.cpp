#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n;
  cin >> n;
  l t = 0, prev = 0;
  bool go = false;
  while(n--){
    l x;
    cin >> x;
    t += go * (x - prev);
    go = !go;
    prev = x;
  }
  cout << (go ? "still running" : to_string(t)) << '\n';
}
