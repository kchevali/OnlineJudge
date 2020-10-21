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

  string s;
  cin >> s;
  l i, d = 0, u = 0, t = 0;
  fpp(i, 1, s.length()) {
    d += s[i] == 'D';
    u += s[i] == 'U';
    t += s[i] != s[i - 1];
  }
  C(d * 2 + (s[0] == 'D') * (s[1] == 'D' ? -1 : 1)) E;
  C(u * 2 + (s[0] == 'U') * (s[1] == 'U' ? -1 : 1)) E;
  C(t) E;
}
