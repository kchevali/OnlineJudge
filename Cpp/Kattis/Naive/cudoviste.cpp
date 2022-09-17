#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m;
  cin >> n >> m;
  l grid[n][m];
  for(l i = 0; i < n; i++){
    string s;
    cin >> s;
    for(l j = 0; j < m; j++){
      grid[i][j] = s[j] == '.' ? 0 : (s[j] == 'X' ? 1 : -100);
    }
  }

  l count[5];
  memset(count, 0 , sizeof(count));

  for(l i = 1; i < n; i++){
    for(l j = 1; j < m; j++){
      l value = grid[i][j]+grid[i-1][j]+grid[i][j-1]+grid[i-1][j-1];
      if(value < 0) continue;
      count[value]++;
    }
  }
  for(l c: count){
    cout << c << "\n";
  }
}
