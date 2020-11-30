#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

const l N = 2e4 + 10;
vl adj[N];
l match[N];
bool vis[N];

l aug(l left) {
  vis[left] = true;
  for (auto& right : adj[left]) {
    if (match[right] == -1 || (!vis[match[right]] && aug(match[right]) == 1)) {
      match[right] = left;
      return 1;
    }
  }
  return 0;
}

l getMatching(l n, l n_left) {
  l count = 0;
  memset(match, -1, sizeof(l) * n);
  for (l i = n_left; i-- > 0;) {
    memset(vis, 0, sizeof(bool) * n_left);
    count += aug(i);
  }
  return count;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, edges;
  cin >> n >> edges;
  for (l i = 0; i < edges; i++) {
    l a, b;
    cin >> a >> b;
    adj[a].push_back(b + n);
  }
  l ans = getMatching(n + n, n);
  // cout << ans << "\n";
  cout << (ans == n ? "YES" : "NO") << "\n";
}
