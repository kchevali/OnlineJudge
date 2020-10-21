#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  while (getline(cin, s)) {
    if ((s.length() & 1) != 0) {
      cout << "trapped\n";
      continue;
    }
    l count = 0, i;
    for (char ch : s) {
      fpp(i, 0, 7) {
        count += (ch & 1);
        ch >>= 1;
      }
    }
    cout << ((count & 1) == 0 ? "free" : "trapped") << "\n";
  }
}
