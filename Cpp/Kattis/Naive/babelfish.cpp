#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  map<string, string> m;
  string line, a, b;
  while (getline(cin, line) && line != "") {
    stringstream s(line);
    s >> a >> b;
    m[b] = a;
  }
  while (getline(cin, line)) cout << (m[line] != "" ? m[line] : "eh") << "\n";
}
