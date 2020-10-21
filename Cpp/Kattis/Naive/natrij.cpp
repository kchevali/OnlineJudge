// To Do Below:
// Certain things have variable types: use type define (ex: MST, weight may be
// double or int)
#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
#define sw(x) cout << setw(x) << std::setfill('0') <<//add zeros to beginning

using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

void read(l &x) {//cannot be use with cin or something
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
  l h1, m1, s1,h2, m2, s2;
  read(h1);read(m1);read(s1);
  read(h2);read(m2);read(s2);

  l x = ((h2+24 - h1)*3600 + (m2-m1)*60 + s2 - s1) % 86400;
  if(!x){
      x = 86400;
  }
  sw(2) (x / 3600) << ":";
  sw(2) ((x % 3600)/60) << ":";
  sw(2) (x % 60) E;

}
