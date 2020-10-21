#include <bits/stdc++.h>
using namespace std;
typedef long long l;

#define fpp(i, a, b) for (i = a; i < b; i++)
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
typedef double o;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  while (true) {
    l n;
    cin >> n;
    if (n == 0) break;
    bool v[10000];
    memset(v, false, sizeof v);
    l count = 0;
    while (!v[n]) {
      v[n] = true;
      string num = to_string(n * n);
      n = stoll((string(8 - num.length(), '0').append(num)).substr(2, 4));
      count++;
    }
    cout << count << "\n";
  }
}
