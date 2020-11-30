#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  bool allGood = true;
  for (l i = 1; i <= n; i++) {
    string s;
    cin >> s;
    if (s != "mumble" && stoll(s) != i) allGood = false;
  }
  cout << (allGood ? "makes sense\n" : "something is fishy\n");
}
