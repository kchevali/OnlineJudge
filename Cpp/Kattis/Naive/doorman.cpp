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
typedef double o;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, i, j, k, men = 0;
  string s;
  cin >> k >> s;
  n = s.length();

  fpp(i, 0, n) {
    men += s[i] == 'M';
    if (abs(men - (i + 1 - men)) > k) {
      if (i < n - 1 && s[i] != s[i + 1]) {
        men += (s[i] != 'M') - (s[i] == 'M');
        swap(s[i], s[i + 1]);
      } else {
        C i E;
        return 0;
      }
    }
  }
  C n E;
}