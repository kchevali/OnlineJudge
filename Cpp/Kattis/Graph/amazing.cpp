#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define v(t) vector<t>
using namespace std;
typedef long long l;

typedef v(l) vl;
typedef v(vl) vvl;
typedef v(bool) vb;
typedef v(vb) vvb;

vvb vis = vvb(100, vb(100, false));
string s;

v(string) dir = {"up", "right", "down", "left"};
v(string) adir = {"down", "left", "up", "right"};
vl dx{0, -1, 0, 1};
vl dy{1, 0, -1, 0};

bool dfs_single(l x, l y) {
  l i;
  fpp(i, 0, 4) {
    l nx = x + dx[i], ny = y + dy[i];
    if (!vis[(100 + nx) % 100][(100 + ny) % 100]) {
      C dir[i] E << flush;

      cin >> s;
      if (s == "solved" || s == "wrong") return true;
      if (s == "wall") continue;
      vis[(100 + nx) % 100][(100 + ny) % 100] = true;
      if (dfs_single(nx, ny)) return true;
      C adir[i] E << flush;
      cin >> s;
      if (s == "solved" || s == "wrong") return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vis[0][0] = true;
  if (!dfs_single(0, 0)) C "no way out" E;
}
