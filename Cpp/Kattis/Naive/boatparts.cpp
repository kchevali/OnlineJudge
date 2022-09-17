#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l p, n;
  cin >> p >> n;
  l day = -1;
  unordered_set<string> s;
  for(l i = 0; i < n; i++){
    string part;
    cin >> part;
    s.insert(part);
    if(s.size() == p && day == -1) day = i + 1;
  }
  cout << (day == -1 ? "paradox avoided" : to_string(day)) << "\n";
}
