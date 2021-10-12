#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  cin >> s;
  l n = s.length();

  for(l i = 1; i < n; i++)
    if((s[i-1] == ':' || s[i-1] == ';') && ((s[i] == ')') || (i < n - 1 && s[i] == '-' && s[i+1] == ')')))
      cout << (i-1) << "\n";
}
