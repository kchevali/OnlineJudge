#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l f[13], mx = 0;
  memset(f,0,sizeof(f));
  string s;
  while(cin >> s){
    char ch = s[0];
    mx = max(mx, ++f[ch == 'A' ? 0 : (ch == 'T' ? 9 : (ch == 'J' ? 10 : (ch == 'Q' ? 11 : (ch == 'K' ? 12 : (ch - '1')))))]);
  }
  cout << mx << "\n";
}
