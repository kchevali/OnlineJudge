#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

const l N = 100 + 10;
string grid[N];
l n, m;

bool explore(l i, l j) {
  if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == '#') return false;
  grid[i][j] = '#';
  explore(i + 1, j);
  explore(i - 1, j);
  explore(i, j + 1);
  explore(i, j - 1);
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  for (l k = 1; cin >> n >> m; k++) {
    for (l i = 0; i < n; i++) cin >> grid[i];

    l count = 0;
    for (l i = 0; i < n; i++)
      for (l j = 0; j < m; j++)
        if (explore(i, j)) count++;
    printf("Case %lld: %lld\n", k, count);
  }
}
