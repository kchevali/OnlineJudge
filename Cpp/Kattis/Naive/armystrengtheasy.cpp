#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

const l N = 100010;
l armyA[N], armyB[N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l cases;
  scanf("%lld", &cases);

  for (l i = 0; i < cases; i++) {
    l a, b;
    scanf("%lld%lld", &a, &b);
    for (l j = 0; j < a; j++) scanf("%lld", &armyA[j]);
    for (l j = 0; j < b; j++) scanf("%lld", &armyB[j]);
    sort(armyA, armyA + a);
    sort(armyB, armyB + b);

    l indexA = 0, indexB = 0;
    while (indexA < a && indexB < b) {
      if (armyA[indexA] < armyB[indexB])
        indexA++;
      else
        indexB++;
    }
    printf(indexA == a ? "MechaGodzilla\n" : "Godzilla\n");
  }
}
