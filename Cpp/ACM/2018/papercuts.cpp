#include <bits/stdc++.h>
using namespace std;
typedef long long l;

  const l N = 1 << 23;
  l n,dp[N];
  string a, b;

l matches(l bit, l index, l prev){
  if(index == n)return -1;
  l k = (prev<<n)+bit ;
  if(dp[k] != -1)return dp[k];
  l i = 1;
  l small = n;
  for(l j = 0; j < n; j++){
    if((bit & i) == 0 && a[j] == b[index])
      small = min(small, matches(bit | i,index+1,j)+ (j == prev + 1 && bit != 0 ? 0 : 1));
    i <<= 1;
  }
  return dp[k] = small;
}

int main() {
  cin >> a >> b;
  n = a.length();
  for(l i = 0; i < N; i++)dp[i] = -1;
  cout << matches(0,0,0) << "\n";
}

/*
abbaaddccee
aaabbeeddcc



*/
