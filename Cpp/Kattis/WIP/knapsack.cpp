#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define pc putchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)

using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

inline bool read(l &x) {  // cannot be use with cin or something
  l c;
  x = 0;
  bool neg = false;
  do {
    c = gc();
    if (c == EOF) return false;
  } while ((c < 48 || c > 57) && c != '-');
  if (c == '-') {
    neg = true;
    c = gc();
  }
  while (c > 47 && c < 58) {
    x = (x << 1) + (x << 3) + c - 48;
    c = gc();
  }
  if (neg) x = -x;
  return true;
}

inline void write(l n) {
  l N = n, rev, count = 0;
  rev = N;
  if (N == 0) {
    pc('0');
    pc('\n');
    return;
  }
  while ((rev % 10) == 0) {
    count++;
    rev /= 10;
  }  // obtain the count of the number of 0s
  rev = 0;
  while (N != 0) {
    rev = (rev << 3) + (rev << 1) + N % 10;
    N /= 10;
  }  // store reverse of N in rev
  while (rev != 0) {
    pc(rev % 10 + '0');
    rev /= 10;
  }
  while (count--) pc('0');
}

vl w, val;

inline l knapsack01(l index, l weight) {
  if (weight <= 0 || index < 0) return 0;
  return max(knapsack01(index - 1, weight),
             w[index] <= weight
                 ? val[index] + knapsack01(index - 1, weight - w[index])
                 : 0);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l cap, n, i;
  while (read(cap) and read(n)) {
    w = vl(n, 0);
    val = vl(n, 0);
    fpp(i, 0, n) {
      read(val[i]);
      read(w[i]);
    }
    write(knapsack01(w.size() - 1, cap));
  }
}
