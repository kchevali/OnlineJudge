#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l rows, cols, r, c;
  cin >> rows >> cols >> r >> c;

  vl rLen(r), cLen(c);
  for (l i = 0; i < r; i++) cin >> rLen[i];
  for (l i = 0; i < c; i++) cin >> cLen[i];

  char grid[rows][cols], ch = (c & 1) != 0 ? 'W' : 'B';
  l y = 0;
  for (l i = 0; i < r; i++) {
    l x = 0;
    for (l j = 0; j < c; j++) {
      if ((c & 1) != 0 || j != 0) ch = ch == 'W' ? 'B' : 'W';
      for (l k = 0; k < rLen[i]; k++) {
        for (l m = 0; m < cLen[j]; m++) {
          grid[y + k][x + m] = ch;
        }
      }
      x += cLen[j];
    }
    y += rLen[i];
  }
  for (auto& row : grid) {
    for (auto& ch : row) {
      cout << ch;
    }
    cout << "\n";
  }
}
