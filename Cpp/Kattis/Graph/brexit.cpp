#include <bits/stdc++.h>
using namespace std;
typedef long long l;

const l N = 200000 + 10, inf = 0x3f3f3f3f3f3f3f3f;
l rem[N];
vector<l> adj[N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  memset(rem, 0, sizeof(rem));

  l n, m, x, leave;
  scanf("%lld%lld%lld%lld", &n, &m, &x, &leave);
  leave--, x--;
  for (l i = 0; i < m; i++) {
    l a, b;
    scanf("%lld%lld", &a, &b);
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
    rem[a]++, rem[b]++;
  }
  queue<l> q;
  q.push(leave);
  rem[leave] = -1;
  while (!q.empty()) {
    l left = q.front();
    q.pop();

    for (l b : adj[left]) {
      if (rem[b] >= 0) {
        rem[b]--;
        if (2 * rem[b] <= adj[b].size()) {
          rem[b] = -1;
          q.push(b);
        }
      }
    }
  }
  printf("%s\n", rem[x] < 0 ? "leave" : "stay");
}