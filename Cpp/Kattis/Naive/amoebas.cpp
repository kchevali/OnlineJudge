#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

const l N = 100 + 10;
string grid[N];
l n, m;

bool explore(l i, l j) {
  if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == '.') return false;
  grid[i][j] = '.';

  for (l a = -1; a <= 1; a++)
    for (l b = -1; b <= 1; b++)
      if (a != 0 || b != 0) explore(i + a, j + b);

  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;
  for (l i = 0; i < n; i++) cin >> grid[i];

  l count = 0;
  for (l i = 0; i < n; i++)
    for (l j = 0; j < m; j++)
      if (explore(i, j)) count++;

  printf("%lld\n", count);
}
