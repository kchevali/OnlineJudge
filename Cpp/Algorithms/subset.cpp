#include "../all.cpp"

vvl dp;     //[setIndex][sumValues]
vl setNum;  // must be sorted
l n;

// Complexity: Number of subsets * weight
bool subsetSum(l index, l sum) {
  if (dp[index][sum] != -1) return dp[index][sum];
  if (sum == 0) return dp[index][sum] = true;
  if (index == 0) return dp[index][sum] = setNum[index] == sum;
  return dp[index][sum] = subsetSum(index - 1, sum) ||
                          (sum >= setNum[index] &&
                           subsetSum(index - 1, sum - setNum[index]));
}

l subsetSumEstimate(l sum, l maxSum) {
  l dx = 0, sign = 1, x;
  do {
    x = sum + sign * dx;
    if (x >= 0 && x <= maxSum && subsetSum(n - 1, x)) return x;
    if ((sign = -sign) < 0) dx++;
  } while (x > 0);
  return 0;
}

void getSubset(l index, l sum, vector<bool> &subset) {
  if (dp[index][sum] != 1 || sum <= 0) return;
  if (sum == setNum[index]) {
    subset[index] = true;
    return;
  }
  if (dp[index - 1][sum]) return getSubset(index - 1, sum, subset);
  subset[index] = true;
  return getSubset(index - 1, sum - setNum[index], subset);
}

vector<bool> getEstimateSubset(l sum, l maxSum) {
  sum = subsetSumEstimate(sum, maxSum);
  vector<bool> subset = vector<bool>(n, false);
  getSubset(n - 1, sum, subset);
  return subset;
}

void start(l maxSum, vl &nums) {
  sort(setNum.begin(), setNum.end());
  n = setNum.size();
  dp = vvl(n, vl(maxSum + 1, -1));
}

int main() {
  vl nums = {1, 2, 3};
  start(200, nums);
  return 0;
}