#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n;
  cin >> n;
  cout << (n / 2 + 1) * (n / 2 + 1 + (n % 2)) << "\n";
}
