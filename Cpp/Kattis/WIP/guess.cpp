#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l a = 1, b = 1000;
  string in;
  while (true) {
    l mid = (a + b) / 2;
    cout << mid << "\n" << flush;
    cin >> in;
    if (in[0] == 'c') return 0;
    if (in[0] == 'l')
      b = mid - 1;
    else
      a = mid + 1;
  }
}