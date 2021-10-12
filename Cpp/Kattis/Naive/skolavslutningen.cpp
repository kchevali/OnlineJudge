#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m, k;
  cin >> n >> m >> k;
  cin.ignore();

  l bits[m];
  memset(bits, 0 , sizeof(bits));

  for(l i = 0; i < n; i++){
    string s;
    cin >> s;
    for(l j = 0; j < m; j++){
      bits[j] |= (1 << (s[j] - 'A'));
    }
  }
  
  bool vis[m];
  memset(vis, 0, sizeof(vis));

  l count = 0;
  for(l i = 0; i < m; i++){
    if(vis[i])continue;
    count++;
    vis[i] = true;
    bool match;
    do{
      match = false;
      for(l j = i + 1; j < m; j++){
        if(vis[j])continue;
        if((bits[i] & bits[j]) != 0){
          vis[j] = match = true;
          bits[i] |= bits[j];
        }
      }

    }while(match);
  }
  cout << count << "\n";
}
