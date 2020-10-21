#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l t, n, i, j, k;
  cin >> t;
  fpp(k, 0, t) {
    cin >> n;
    queue<l> a;
    vector<l> res(n, 0);
    l index = 1;
    fpp(i, 0, n) a.push(i);
    fpp(i, 0, n) {
      fpp(j, -1, i) {
        a.push(a.front());
        a.pop();
      }
      res[a.front()] = index++;
      a.pop();
    }
    for (auto x : res) cout << x << " ";
    cout << "\n";
  }
}