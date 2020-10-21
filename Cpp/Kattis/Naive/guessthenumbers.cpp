#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

l nums[10], n, res;
string s;
l counter = 0, pos[50];

class Expression {
 public:
  Expression *left = NULL, *right = NULL;
  l index = -1;
  l var = -1;
  Expression(l a, l b) { parse(a, b); }

  void parse(l a, l b) {
    if (a > b) return;
    if (a == b && s[a] >= 'a' && s[a] <= 'z') {
      l letter = s[a] - 'a';
      if (pos[letter] == -1) pos[letter] = counter++;
      var = pos[letter];
      index = a;
      return;
    }

    l brac = 0, opScore = 0;
    for (l i = a; i < b; i++) {
      if (s[i] == '(')
        brac++;
      else if (s[i] == ')')
        brac--;
      else if (brac == 0) {
        l score = 0;
        switch (s[i]) {
          case '*':
            score++;
          case '+':
          case '-':
            score++;
        }
        if (score > opScore) {
          index = i;
          opScore = score;
        }
      }
    }
    if (index != -1) {
      left = new Expression(a, index - 1);  // 12+1
      right = new Expression(index + 1, b);
    } else if (a < b) {  // all ()
      parse(a + 1, b - 1);
    }
  }

  l solve() {
    if (var >= 0) return nums[var];
    l a = left->solve(), b = right->solve();
    return s[index] == '*' ? (a * b) : (s[index] == '+' ? (a + b) : (a - b));
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  while (cin >> n && n > 0) {
    for (l i = 0; i < n; i++) cin >> nums[i];
    cin >> res >> s;
    counter = 0;
    memset(pos, -1, sizeof(pos));
    Expression ex = Expression(0, s.length() - 1);
    bool solved = false;
    sort(nums, nums + n);
    do {
      // for (l i = 0; i < n; i++) cout << nums[i] << " ";
      // cout << "\n";
      if (ex.solve() == res) {
        solved = true;
        // break;
      }
    } while (next_permutation(nums, nums + n));
    cout << (solved ? "YES" : "NO") << "\n";
  }
}

/*
4
2 4 5 7 81
(a+b)*(c+d)
*/