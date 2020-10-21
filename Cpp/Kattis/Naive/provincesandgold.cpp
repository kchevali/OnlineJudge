#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l g, s, c;
  cin >> g >> s >> c;

  l pts = g * 3 + s * 2 + c;
  string victory = "", treasure = "Copper";
  if (pts >= 8)
    victory = "Province";
  else if (pts >= 5)
    victory = "Duchy";
  else if (pts >= 2)
    victory = "Estate";

  if (pts >= 6)
    treasure = "Gold";
  else if (pts >= 3)
    treasure = "Silver";
  cout << (victory == "" ? treasure : victory + " or " + treasure) << "\n";
}