#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef pair<l, l> ll;

const l N = 100000 + 10, M = 100000 + 10;
l w[N];   // weights
ll s[M];  // sellers (fish count,price/kg)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m;
  scanf("%lld%lld", &n, &m);
  for (l i = 0; i < n; i++) scanf("%lld", w + i);
  for (l i = 0; i < m; i++) scanf("%lld%lld", &(s[i].first), &(s[i].second));

  sort(w, w + n, greater<l>());                                                  // big fish first
  sort(s, s + m, [](const ll &a, const ll &b) { return a.second > b.second; });  // prime price first

  l f = 0, total = 0;  // fish
  for (l i = 0; i < m && f < n; i++) {
    auto &[count, price] = s[i];
    for (l j = 0; j < count && f < n; j++, f++) {
      total += price * w[f];
    }
  }
  printf("%lld\n", total);
}
