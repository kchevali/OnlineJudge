#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)

using namespace std;

typedef long long l;
typedef vector<l> vl;
typedef vector<bool> vb;
typedef vector<vl> vvl;

void read(l &x) {  // cannot be use with cin or something
  l c = gc();
  x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc())
    ;
  if (c == '-') {
    neg = 1;
    c = gc();
  }
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
  if (neg) x = -x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l w, n, i, j;
  read(w);
  read(n);
  vl v = vl(n + 2, 0);
  fpp(i, 0, n) { read(v[i + 1]); }
  v[n + 1] = w;

  vb ans = vb(w + 1, 0);
  fpp(i, 0, n + 2) {
    fpp(j, i + 1, n + 2) { ans[v[j] - v[i]] = 1; }
  }
  string s = "";
  fpp(i, 0, w + 1) {
    if (ans[i]) {
      s += to_string(i) + " ";
    }
  }
  C s E;
}
