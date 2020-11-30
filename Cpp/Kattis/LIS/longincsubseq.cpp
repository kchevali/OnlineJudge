#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

template <class T>
vector<l> LIS_FAST(vector<T> &v) {
  vector<l> p(v.size(), -1);
  vector<l> t(v.size(), 0);

  l lis = 1;
  for (l i = 1; i < v.size(); i++) {
    if (v[i] <= v[t[0]]) {
      t[0] = i;
    } else if (v[i] > v[t[lis - 1]]) {
      p[i] = t[lis - 1];
      t[lis++] = i;
    } else {
      l a = -1, b = lis - 1;
      while (b - a > 1) {
        l m = a + (b - a) / 2;
        if (v[t[m]] >= v[i])
          b = m;
        else
          a = m;
      }
      p[i] = t[b - 1];
      t[b] = i;
    }
  }

  vector<l> ans;
  for (l i = t[lis - 1]; i >= 0; i = p[i]) {
    ans.push_back(i);
  }
  reverse(ans.begin(), ans.end());

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n;
  while (cin >> n) {
    vl nums(n);
    for (l i = 0; i < n; i++) cin >> nums[i];
    vl ans = LIS_FAST<l>(nums);
    cout << ans.size() << "\n";
    for (l i = 0; i < ans.size(); i++) cout << (ans[i]) << " ";
    cout << "\n";
  }
}
