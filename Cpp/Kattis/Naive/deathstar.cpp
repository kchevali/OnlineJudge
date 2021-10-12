#include <bits/stdc++.h>
using namespace std;
typedef int l;
#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

#define d10 %d %d %d %d %d %d %d %d %d %d
#define d100 d10 d10 d10 d10 d10 d10 d10 d10 d10 d10
#define d1000 d100 d100 d100 d100 d100 d100 d100 d100 d100 d100
#define d10000 d1000 d1000 d1000 d1000 d1000 d1000 d1000 d1000 d1000 d1000
#define d100000 d10000 d10000 d10000 d10000 d10000 d10000 d10000 d10000 d10000 d10000
#define d1000000 d100000 d100000 d100000 d100000 d100000 d100000 d100000 d100000 d100000 d100000

#define x1 x + __COUNTER__,
#define x9 x1 x1 x1 x1 x1 x1 x1 x1 x1
#define x10 x9 x1
#define x99 x10 x10 x10 x10 x10 x10 x10 x10 x10 x9
#define x100 x99 x1
#define x999 x100 x100 x100 x100 x100 x100 x100 x100 x100 x99
#define x1000 x999 x +  __COUNTER__
// #define x9999 x1000 x1000 x1000 x1000 x1000 x1000 x1000 x1000 x1000 x999
// #define x10000 x9999 x1
// #define x99999 x10000 x10000 x10000 x10000 x10000 x10000 x10000 x10000 x10000 x9999
// #define x100000 x99999 x1
// #define x999999 x100000 x100000 x100000 x100000 x100000 x100000 x100000 x100000 x100000 x99999
// #define x1000000 x999999 x +  __COUNTER__


#define gc() getchar_unlocked()

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  scanf("%d", &n);

  int x[1000000];
  

  for(l i = 0, idx = 1000; i < n; i++){
    l y = 0;
    for(l j = 0; j < n; j++, idx++){
      if(idx >= 1000){
        idx = 0;
        scanf(STRINGIFY(d1000), x1000);
      }
      y |= x[idx];
    }
    printf("%d ", y);
  }
  printf("\n");
}
