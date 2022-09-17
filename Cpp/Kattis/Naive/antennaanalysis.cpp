#include <bits/stdc++.h>
using namespace std;
typedef long long l;
#define gc getchar_unlocked

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

#define pc(x) putchar_unlocked(x);
inline void writeInt (l n)
{
    l N = n, rev, count = 0;
    rev = N;
    if (N == 0) { pc('0'); return ;}
    while ((rev % 10) == 0) { count++; rev /= 10;} //obtain the count of the number of 0s
    rev = 0;
    while (N != 0) { rev = (rev<<3) + (rev<<1) + N % 10; N /= 10;}  //store reverse of N in rev
    while (rev != 0) { pc(rev % 10 + '0'); rev /= 10;}
    while (count--) pc('0');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    l n, c;
    read(n);
    read(c);
    n *= c;

    l a = -1e9, b = -1e9;
    for(l i = 0; i < n; i+=c){
        l x;
        read(x);
        a = max(a, i - x), b = max(b, i + x);
        writeInt(max(a + x, b - x) - i);
        pc(' ');
    }
    pc('\n');
}