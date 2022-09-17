#include <bits/stdc++.h>
using namespace std;
typedef long long l;

inline l value(char& x){
  return x == '\'' ? 27 : (x == ' ' ? 26 : (x - 'A'));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  cin.ignore();

  for(l i = 0; i < n; i++){
    string s;
    getline(cin, s);
    l total = 0;
    for(l j = 1, len = s.length(); j < len; j++){
      l prev = value(s[j-1]), x = value(s[j]);
      l diff = max(prev, x) - min(prev, x);
      // cout << "'" << s[j-1] << "' " << prev << " " << abs(x - prev) << " " << (min(x, prev) + 28) << " " << max(x, prev) << "\n";
      total += min(diff, 28 - diff);
    }
    cout << fixed << setprecision(8) << (s.length() + M_PI * 60.0 * total / (28.0 * 15.0)) << "\n";
  }
}
