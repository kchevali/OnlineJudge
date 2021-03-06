#include <bits/stdc++.h>
using namespace std;

string convert(string s, int numRows) {
  int n = s.length();
  if (numRows == 1 || numRows >= n) return s;

  int p = 2 * numRows - 2;
  string o(n, 0);

  for (int i = 0, index = 0; i < numRows; i++) {
    for (int j = 0;; j++) {
      int k = p * j + i, m = p * j + p - i;
      if (k >= n) break;
      o[index++] = s[k];
      if (i > 0 && i < numRows - 1 && m < n) o[index++] = s[m];
    }
  }
  return o;
}

int main() {
  string in = "PAYPALISHIRING";
  int rows = 4;
  string out = convert(in, rows);
  string ans = "PINALSIGYAHRPI";

  cout << "SOL:" << out << "\n";
  cout << "ANS:" << ans << "\n";
}

/*
get new position formula
Row 0: 6x+0
Row 1: 6x+1 and 6x+5
Row 2: 6x+2 and 6x+4
Row 3: 6x+3

x:
*/