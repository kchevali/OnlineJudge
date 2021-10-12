#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l w, n;
  cin >> w >> n;
  l t = 0;
  for(l i = 0; i < n; i++){
    l a, b;
    cin >> a >> b;
    t += a * b;
  }
  cout << (t / w) << "\n";
}
