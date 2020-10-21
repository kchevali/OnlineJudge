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

  string a, b;
  cin >> a >> b;
  l n = a.length(), m = b.length(), len = min(n, m), i, j, k;
  fpp(i, 0, len) if (a[i] != b[i]) break;
  for (j = n - 1, k = m - 1; i <= j; j--, k--)
    if (a[j] != b[k]) break;
  C max(0LL, (m - (n - (j - i + 1)))) E;
}

//***
//*##**