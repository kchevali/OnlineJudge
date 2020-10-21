#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define fpp(i, a, b) for (i = a; i < b; i++)
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l a, b;
  cin >> a >> b;
  C(a <= (1LL << (b + 1)) - 1 ? "yes" : "no") E;
}
