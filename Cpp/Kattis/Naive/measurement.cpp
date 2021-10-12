#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  double x;
  string a, t, b;
  cin >> x >> a >> t >> b;

  unordered_map<char, l> units({
    {'t',0},
    {'i',1},
    {'f',2},
    {'y',3},
    {'c',4},
    {'m',6},
    {'l',7},
  });

  double values[8] = {1, 1000, 12, 3, 22, 10, 8, 3};

  l idxA = units[a[0]] + (a[1] == 'u') * 3, idxB = units[b[0]] + (b[1] == 'u') * 3;
  double prod = 1;
  for(l i = min(idxA, idxB) + 1, j = max(idxA, idxB); i <= j; i++) prod *= values[i];
  cout << fixed << setprecision(13) << (idxA < idxB ? (x / prod) : (x * prod)) << "\n";
}
