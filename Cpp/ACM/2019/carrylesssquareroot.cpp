#include <bits/stdc++.h>
using namespace std;
typedef long long l;

string n;
vector<string> sub;
l nLen;

string sq(string& s, l len) {
  string out;
  l length = s.length();
  out.resize(len);
  for (l i = 0; i < len; i++) {
    l digit = 0;
    for (l j = 0, x = length - 1 - i, y = length - 1; j <= i; j++, x++, y--) {
      l a = x >= 0 ? s[x] - '0' : 0;
      l b = y >= 0 ? s[y] - '0' : 0;
      digit += a * b;
    }
    out[len - i - 1] = (digit % 10) + '0';
  }
  return out;
}

string bfs() {
  string x;
  queue<tuple<string, string, l>> q;
  q.push(make_tuple(x, x, 1));
  string best = "-1";

  while (!q.empty()) {
    string a, aSq;
    l length;
    tie(a, aSq, length) = q.front();
    q.pop();

    if (a.length() > best.length() && best != "-1") return best;
    if (aSq == n && (a < best || best == "-1")) best = a;
    if (length > nLen) continue;

    for (l i = 0; i < 10; i++) {
      string s = to_string(i) + a;
      string sqr = sq(s, length);
      if (sqr == sub[length]) q.push(make_tuple(s, sqr, length + 1));
    }
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;
  sub.push_back("");
  nLen = n.size();
  for (l i = nLen - 1; i >= 0; i--) {
    sub.push_back(n[i] + sub[sub.size() - 1]);
  }

  string out = bfs();
  bool removeZero = true;
  for (char ch : out) {
    if (ch != '0' || !removeZero) {
      cout << ch;
      removeZero = false;
    }
  }
  cout << "\n";
}
