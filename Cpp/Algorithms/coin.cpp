
typedef long long l;
// Coin Change (CC)
// Given a set of coin values and the target amount V, what is the minimum
// number of coins that we must use to represent V? Assume we have infinite
// amount of coins for each value.
//  e.g. coinValue = {1, 5, 10, 15}, V = 12. Well we need 3 coins: one 10 and
//  two 1’s.
// Complexity O(nV), where n is the number of coin values, V is the target
// value. There are similar problems like how many ways are there to achieve the
// target value. What is the minimum number of coins that we must use to
// represent a target value if there are limited amount of coins? (Both included
// in following code)

// class CoinChange {
//     // 2 is size of coinValue, 100 is the target value
// l ways[2][101];

//     l coinValue[] = {1, 5};
//     l N = 2; // size of coinValue

//     void main(String[] args) {
//         //min CC, unlimited amount of coins
//         double[] dp = new double[11];
//         Arrays.fill(dp, Double.POSITIVE_INFINITY);
//         dp[0] = 0;
//         for(l i = 0; i < dp.length; i++) {
//             for(l j = 0; j < N; j++) {
//                 if(i + coinValue[j] < dp.length)
//                     dp[i + coinValue[j]] = Math.min(dp[i + coinValue[j]],
//                     dp[i] + 1);
//             }
//         }
//         //Ways: number of ways to get total value 100 with different coins
//         //Ways top-down example
//         for(l[] a : ways) Arrays.fill(a,  -1);
//         System.out.prlln(way(0, 100));

//         //Ways bottom-up example
//         l[] dp1 = way(100);
//         System.out.prlln(dp1[100]);
//     }

// //Ways, top-down, may stack overflow if value is too large,
// //then use bottom-up approach
//     l way(l type, l value) {
//         if(value == 0) return 1;
//         if(value < 0 || type == N) return 0;
//         if(ways[type][value] != -1) return ways[type][value];
//         return ways[type][value] = way(type + 1, value) + way(type, value -
//         coinValue[type]);
//     }

//     /*  bottom-up, build the table only once!, let value be the largest
//     possible value.
//      *  once get the array, use dp[value] to get the ways
//      *  May use long[] if the value and the size of the coin value is large.
//      *  complexity nV, n is the value, V is the size of coinValue
//      */
//     l[] way(l value) {
//         l[] dp = new l[value + 1];
//         dp[0] = 1;
//         for(l i = 0; i < N; i++) for(l j = coinValue[i]; j <= value; j++)
//             dp[j] += dp[j - coinValue[i]];
//         return dp;
//     }

//     // Coin Change with limited amount of coins
//     void cc() {
//         l V = 11; // V is the target amount
//         l[] coins = {1, 1, 2, 3, 4}; //coin values. Two 1s, one 2, one 3, and
//         one 4 l[] dp = new l[V + 1]; Arrays.fill(dp, Integer.MAX_VALUE);
//         dp[0] = 0;
//         for(l c : coins) for(l i = dp.length - 1 - c; i >= 0; i--)
//             if(dp[i] < Integer.MAX_VALUE) dp[i + c] = Math.min(dp[i + c],
//             dp[i] + 1);

//         dp[V]; // is the minimum number of coins we must use to get V
//     }
// }

// complexity coins.size() * total
// https://www.youtube.com/watch?v=Y0ZqKpToTic

#define inf 0x3f3f3f3fLL
const l MAX_COIN = 10, MAX_TOTAL = 500;

// INFINITE COIN ALGORITHMS
l dp[MAX_COIN][MAX_TOTAL + 1];  // infCC,wa
vl coins;

l infCC2(l c, l t) {
  if (dp[c][t] != -1) return dp[c][t];
  if (t == 0) return dp[c][t] = 0;
  return dp[c][t] = (t >= coins[c] ? min(c > 0 ? infCC2(c - 1, t) : inf,
                                         1 + infCC2(c, t - coins[c]))
                                   : infCC2(c - 1, t));
}
l infCC(l total) { return infCC2(coins.size() - 1, total); }

l ways2(l c, l t) {
  if (dp[c][t] != -1) return dp[c][t];
  if (t == 0) return dp[c][t] = 1;
  return dp[c][t] = t >= coins[c]
                        ? (c > 0 ? ways2(c - 1, t) : 0) + ways2(c, t - coins[c])
                        : ways2(c - 1, t);
}
l ways(l total) { return ways2(coins.size() - 1, total); }

void resetINF() {
  for (l i = 0; i < MAX_COIN; i++)
    for (l j = 0; j <= MAX_TOTAL; j++) dp[i][j] = -1;
}

// FINITE COIN ALGORITHMS
// Coin Change with limited amount of coins
l limCC(l total) {
  l dp2[total + 1];  // reset is required
  for (l j = 0; j <= total; j++) dp2[j] = inf;
  dp2[0] = 0;
  for (l c : coins)
    for (l i = total - c; i >= 0; i--)
      if (dp2[i] != inf) dp2[i + c] = min(dp2[i + c], dp2[i] + 1);
  return dp2[total];
}

l limWays(l total) {
  l dp2[total + 1];  // reset is required
  for (l j = 0; j <= total; j++) dp2[j] = 0;
  dp2[0] = 1;
  for (l c : coins)
    for (l i = total; i >= c; i--) dp2[i] += dp2[i - c];
  return dp2[total];
}

int main() {
  for (l i = 0; i < 10; i++) coins.push_back(1);
  coins.push_back(5);
  coins.push_back(10);
  // coins.push_back(8);
  resetINF();

  for (l i = 0; i <= 20; i++)
    //   cout << "Min Coins [" << i << "] " << ways(i) << "\n";
    cout << i << " -> " << limWays(i) << "\n";
}