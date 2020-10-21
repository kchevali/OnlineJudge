#include <bits/stdc++.h>
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
using namespace std;
typedef long long l;
typedef pair<l, l> ll;
typedef deque<ll> qll;

const l MAXN = 1000;

char grid[MAXN][MAXN];
bool vis[MAXN][MAXN];
l depth[MAXN][MAXN];
l ans[26];

void read(l &x) {
  l c = gc();
  x = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc())
    ;
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l h, w, i, j, x, y;

  read(h);
  read(w);
  l n = h * w;
  fpp(i, 0, 26) ans[i] = n;
  qll q;
  fpp(i, 0, h) fpp(j, 0, w) {
    grid[i][j] = gc();
    depth[i][j] = n;
    while (grid[i][j] < 'A' || grid[i][j] > 'Z') grid[i][j] = gc();
    if (grid[i][j] == 'W') {
      q.emplace_back(j, i);
      depth[i][j] = -1;
    }
  }
  while (!q.empty()) {
    tie(x, y) = q.front();
    q.pop_front();
    fpp(i, -1, 2) {
      fpp(j, -1, 2) {
        if (i == 0 && j == 0) continue;
        l nx = x + j, ny = y + i;
        if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
        l w = grid[y][x] != grid[ny][nx], dist = depth[y][x] + w;
        if (dist < depth[ny][nx]) {
          depth[ny][nx] = dist;
          if (w == 1)
            q.emplace_back(nx, ny);
          else
            q.emplace_front(nx, ny);
        }
      }
    }
  }

  fpp(i, 0, h) fpp(j, 0, w) {
    if (grid[i][j] == 'W') continue;
    l c = grid[i][j] - 'A';
    if (depth[i][j] < ans[c]) {
      ans[c] = depth[i][j];
    }
  }

  fpp(i, 0, 26) if (ans[i] >= 0 && ans[i] < n)
      printf("%c %lld\n", char(i + 'A'), ans[i]);
  return 0;
}
