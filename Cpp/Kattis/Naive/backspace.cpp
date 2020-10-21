#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s, out;
  cin >> s;
  for (char ch : s) {
    if (ch == '<')
      out.pop_back();
    else
      out.push_back(ch);
  }
  cout << out << "\n";
}