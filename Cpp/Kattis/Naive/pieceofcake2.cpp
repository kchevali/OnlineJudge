#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, h, v;
  cin >> n >> h >> v;

  cout << (4 * max(h,(n-h)) * max(v, (n-v))) << "\n";
}
