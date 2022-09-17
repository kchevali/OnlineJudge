#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, p, s;
  cin >> n >> p >> s;

  for(l i = 0; i < s; i++){
    l m;
    cin >> m;
    bool keep = false;
    for(l j = 0; j < m; j++){
      l x;
      cin >> x;
      keep = keep or (x == p);
    }
    cout << (keep ? "KEEP" : "REMOVE") << "\n";
  }
}
