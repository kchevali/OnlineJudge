#include <bits/stdc++.h>
using namespace std;
#define fpp(i, a, b) for (i = a; i < b; i++)
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l t, n, m, p, q, i, j, k;
  cin >> t;
  fpp(i, 0, t) {
    cin >> n;
    map<string, map<string, l>> mp;
    fpp(j, 0, n) {
      string pizza, ingr;
      cin >> pizza >> m;
      vector<string> ingrs(m);

      fpp(k, 0, m) cin >> ingrs[k];
      cin >> p;
      fpp(q, 0, p) {
        cin >> ingr;
        fpp(k, 0, m) mp[ingrs[k]][ingr]++;
      }
    }
    vector<pair<string, string>> out;
    for (auto &key : mp)
      for (auto &key2 : key.second) {
        cout << "C: " << key.first << " " << key2.first << " " << key2.second
             << "\n";
        if (key2.second == n)
          out.emplace_back(make_pair(key.first, key2.first));
      }
    sort(out.begin(), out.end());
    fpp(j, 0, out.size()) cout << "(" << out[j].first << ", " << out[j].second
                               << ")\n";
  }
}
