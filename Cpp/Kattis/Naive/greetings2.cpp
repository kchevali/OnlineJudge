#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  l len = s.length() * 2;
  cout << 'h';
  for(l i = 4; i < len; i++) cout << 'e';
  cout << "y\n";
}
