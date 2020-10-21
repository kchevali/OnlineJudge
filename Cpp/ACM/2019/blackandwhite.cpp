#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;

  string grid[n];

  for (l i = 0; i < n; i++) {
    cin >> grid[i];
  }

  bool correct = true;
  for (l i = 0; i < n; i++) {
    l row = 0, col = 0;
    for (l j = 0; j < n; j++) {
      row += grid[i][j] == 'B';
      col += grid[j][i] == 'B';
      if (i >= 2 && grid[j][i] == grid[j - 1][i] && grid[j][i] == grid[j - 2][i]) correct = false;
      if (j >= 2 && grid[i][j] == grid[i][j - 1] && grid[i][j] == grid[i][j - 2]) correct = false;
    }
    correct = correct && 2 * row == n && 2 * col == n;
  }
  cout << correct << "\n";
}
