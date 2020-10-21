#include <bits/stdc++.h>
using namespace std;
typedef long long l;

const l SIZE = 1000, COUNT = 100;
l dp[SIZE][SIZE * COUNT];  //[setIndex][sumValues]
l setNum[SIZE];            // must be sorted
l n;

bool subsetSum(l index, l sum) {
  if (dp[index][sum] != -1) return dp[index][sum];
  if (sum == 0) return dp[index][sum] = true;
  if (index == 0) return dp[index][sum] = setNum[index] == sum;
  return dp[index][sum] = subsetSum(index - 1, sum) ||
                          (sum >= setNum[index] &&
                           subsetSum(index - 1, sum - setNum[index]));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m;
  l ns[n], ms[m];
  for (l i = 0; i < n; i++) cin >> ns[i];
  for (l i = 0; i < m; i++) cin >> ms[i];
}