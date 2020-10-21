// To Do Below:
// Certain things have variable types: use type define (ex: MST, weight may be
// double or int)
#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
using namespace std;
typedef long long l;
typedef pair<l, l> ll;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<vb> vvb;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vll v;

  string s;
  l x = 0, y = 0;
  l minX = 0, minY = 0, maxX = 0, maxY = 0;
  while (cin >> s) {
    if (s == "up") {
      v.PB(make_pair(0, -1));
      if (--y < minY) minY = y;
    } else if (s == "right") {
      v.PB(make_pair(1, 0));
      if (++x > maxX) maxX = x;
    } else if (s == "down") {
      v.PB(make_pair(0, 1));
      if (++y > maxY) maxY = y;
    } else if (s == "left") {
      v.PB(make_pair(-1, 0));
      if (--x < minX) minX = x;
    }
  }
  l h = maxY - minY + 1, w = maxX - minX + 1;
  vvb grid = vvb(h, vb(w, false));
  x = -minX;
  y = -minY;
  for (ll p : v) {
    grid[y += p.second][x += p.first] = true;
  }
  l i, j;
  s = "";
  fpp(i, -1, h + 1) {
    fpp(j, -1, w + 1) {
      if (i == -1 || j == -1 || i == h || j == w) {
        s += "#";
      } else if (i == -minY && j == -minX) {
        s += "S";
      } else if (i == y && j == x) {
        s += "E";
      } else {
        s += grid[i][j] ? "*" : " ";
      }
    }
    s += "\n";
  }
  C s;
}
