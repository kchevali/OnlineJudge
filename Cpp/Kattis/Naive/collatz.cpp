#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

l next(l x) {
  if (x & 1)
    return x = 3 * x + 1;
  else
    return x >> 1;
}

l contains(vl &v, l x) {
  l i, len = v.size();
  fpp(i, 0, len) {
    if (v[i] == x) {
      return i;
    }
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l a, b;
  cin >> a >> b;
  while (a + b) {
    l a1 = a;
    l b1 = b;

    vl vA = vl(600, 1);
    l i = 0;
    while (a1 != 1) {
      vA[i++] = a1;
      a1 = next(a1);
    }

    l stepsB = 0;
    a1 = contains(vA, b1);
    while (a1 == -1) {
      b1 = next(b1);
      stepsB++;
      a1 = contains(vA, b1);
    }

    C a _ "needs" _ a1 _ "steps," _ b _ "needs" _ stepsB _
          "steps, they meet at" _ b1 E;
    cin >> a >> b;
  }
}
