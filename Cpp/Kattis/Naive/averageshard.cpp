#include <bits/stdc++.h>
using namespace std;
typedef int l;

l cs[200010];

int main() {
  l tt;
  scanf("%d", &tt);
  while(tt--){
    l n, m, x, count = 0;
    scanf("%d%d",&n, &m);
    l csTot = 0, ecoTot = 0;
    for(l i = 0; i < n; i++){
      scanf("%d", cs + i);
      csTot += cs[i];
    }
    for(l i = 0; i < m; i++){
      scanf("%d", &x);
      ecoTot += x;
    }
    double csAvg =  (double)csTot  / n;
    double ecoAvg = (double)ecoTot / m;
    for(l i = 0; i < n; i++) count += cs[i] < csAvg && cs[i] > ecoAvg;
    printf("%d\n", count);
  }
}
