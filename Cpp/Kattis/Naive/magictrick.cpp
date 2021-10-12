#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  bool f[26];
  memset(f, 0 , sizeof(f));
  string s;
  cin >> s;
  for(char ch: s){
    l idx = ch - 'a';
    if(f[idx]){
      cout << "0\n";
      return 0;
    }
    f[idx] = true;
  }
  cout << "1\n";
}
