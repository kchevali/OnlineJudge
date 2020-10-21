
#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, i, j;
  cin >> n;
  while (n) {
    vl v = vl(n, 0);
    fpp(i, 0, n) {
      cin >> v[i];
      v[i]--;
    }
    string s;
    getline(cin, s);
    getline(cin, s);
    while (s.size() % n) {
      s += " ";
    }
    string sol = "";
    fpp(i, 0, s.size()) { sol += s[(i / n) * n + v[i % n]]; }
    C "'" << sol << "'" E;
    cin >> n;
  }
}
