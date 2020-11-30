#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;
#define scan(x) \
  l x;          \
  scanf("%lld", &x);

struct doll {
  l w, h;
};

const l N = 1e5 + 10;
doll nums[N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  scan(c);
  for (l i = 0; i < c; i++) {
    scan(n);
    for (l j = 0; j < n; j++) scanf("%lld%lld", &nums[j].w, &nums[j].h);
    sort(nums, nums + n, [](const doll& a, const doll& b) { return a.h == b.h ? a.w > b.w : a.h < b.h; });
    vector<doll> v;
    v.push_back(nums[n - 1]);

    for (int i = n - 2; i >= 0; i--) {
      int lo = 0, hi = v.size() - 1, mid;

      while (lo <= hi) {
        mid = (hi + lo) / 2;
        if (v[mid].h == nums[i].h || v[mid].w <= nums[i].w)
          lo = mid + 1;
        else
          hi = mid - 1;
      }

      if (lo >= v.size())
        v.push_back(nums[i]);
      else {
        v[lo].h = nums[i].h;
        v[lo].w = nums[i].w;
      }
    }
    printf("%d\n", (int)v.size());
  }
}
