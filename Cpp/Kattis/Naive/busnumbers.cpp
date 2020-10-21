#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

void read(l &x) {
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

  l n;
  read(n);
  l i;
  vl v = vl(n, 0);
  fpp(i, 0, n) { read(v[i]); }
  sort(v.begin(), v.end());
  l start = -1;
  string s = "";
  fpp(i, 1, n) {
    if (v[i] == v[i - 1] + 1) {
      if (start == -1) {
        start = v[i - 1];
      }
    } else {
      if (start != -1) {
        s += to_string(start) + (v[i-1] - start == 1 ? " " : "-") + to_string(v[i - 1]) + " ";
        start = -1;
      } else {
          s += to_string(v[i-1]) + " ";
      }
    }
  }
  if (start != -1) {
    s += to_string(start) + (v[i-1] - start == 1 ? " " : "-") + to_string(v[i - 1]);
    }else{
    s += to_string(v[v.size()-1]);
    }
    C s E;
}
