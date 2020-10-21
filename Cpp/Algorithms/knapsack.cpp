#include "../Template.cpp"
typedef vector<bool> vb;
typedef vector<l> vl;
vl w, val, dp;
l n;
vb ans;
inline l knapsack(l index, l weight) {
  // C "index:" _(index + weight * n) E;
  if (weight <= 0 || index < 0) return 0;
  if (dp[index + weight * n] != -1) return dp[index + weight * n];
  return dp[index + weight * n] =
             max(knapsack(index - 1, weight),
                 w[index] <= weight
                     ? val[index] + knapsack(index - 1, weight - w[index])
                     : 0);
}

inline void readKnapsack(l index, l weight) {
  if (weight <= 0 || index < 0) return;
  if (index == 0 && dp[index + weight * n] == val[index]) {
    ans[index] = true;
    return;
  }
  // C "Current:" _ dp[index + weight * n] _
  //     "NExt:" _(dp[index - 1 + (weight - w[index]) * n] + val[index]) E;
  if (dp[index + weight * n] == dp[index - 1 + weight * n])
    return readKnapsack(index - 1, weight);
  ans[index] = true;
  readKnapsack(index - 1, weight - w[index]);
}

inline void getKnapsack(l cap) {
  // w = vl(n, 0);
  // val = vl(n, 0);
  n = w.size();
  dp = vl(n * (cap + 1), -1);
  ans = vb(n, false);
  C knapsack(n - 1, cap) E;
  readKnapsack(n - 1, cap);
}

int main() {
  w = {1, 2, 4, 5};
  val = {1, 2, 4, 3};
  getKnapsack(1);
  l c = 0;
  for (const auto &x : ans) {
    C x _ "";
  }
}