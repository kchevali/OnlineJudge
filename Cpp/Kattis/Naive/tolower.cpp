#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m, i, j, k;
  cin >> n >> m;
  l x = n;
  fpp(i, 0, n) {
    bool pass = true;
    fpp(j, 0, m) {
      string s;
      cin >> s;
      if (pass) fpp(k, 1, s.length()) if (s[k] >= 'A' && s[k] <= 'Z') {
          x--;
          pass = false;
          break;
        }
    }
  }
  C x E;
}
