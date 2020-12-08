#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> x;

  void solve(int a, int c) {
    if (a >= c - 1) return;
    int b = a, j = c - 1;
    while (b < j) {
      while (b < j && (x[b] & 1) == 1) b++;
      while (b < j && (x[j] & 1) == 0) j--;
      swap(x[b], x[j]);
    }
    for (int i = a; i < c; i++) x[i] /= 2;
    solve(a, b);
    solve(b, c);
    for (int i = a; i < b; i++) x[i] = 2 * x[i] + 1;
    for (int i = b; i < c; i++) x[i] = 2 * x[i];
  }

  vector<int> beautifulArray(int N) {
    x.resize(N);
    iota(x.begin(), x.end(), 1);
    solve(0, N);
    return x;
  }
};