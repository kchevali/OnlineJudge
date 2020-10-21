#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

vl dp;
l n;
string s;

int get(int i, int left, int t) { return i + (left + t * n) * n; }

int L(int i, int t) {
  return ((s[i] == '(' && t != 1) || (s[i] == ')' && t == 1))
             ? 1
             : 0;  // count a left bracket if is left and not inverting
                   // count a left bracket if is right and inverting
}

bool isValid(int i, int left, int t) {
  if (i == n) {
    return left == n - left;
  }
  l index = get(i, left, t);
  if (dp[index] >= 0) {
    return dp[index];
  }
  if (left < i - left) {
    return dp[index] = 0;
  }
  dp[index] =
      ((t == 0 &&
        isValid(i, left,
                1)) ||  // it is before and inverting it will still be valid
       (t == 1 &&
        isValid(i, left, 2)) ||  // it is inverting and after will be valid
       (isValid(i + 1, left + L(i, t),
                t)));  // it is valid if we look at the next bracket
  return dp[index];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> s;
  n = s.length();
  dp = vl(n * n * 3, -1);
  C(isValid(0, 0, 0) ? "possible" : "impossible") E;
  return 0;
}
