#include <stdio.h>
#define gc getchar_unlocked
#define pc putchar_unlocked

void read(int* x) {
  int c = gc();
  *x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc())
    ;
  if (c == '-') {
    neg = 1;
    c = gc();
  }
  for (; c > 47 && c < 58; c = gc()) {
    *x = (*x << 1) + (*x << 3) + c - 48;
  }
  if (neg) *x = -(*x);
}


void writeMyNum (int n)
{
    int N = n, rev = n, count = 0;
    if (N == 0) { pc('0'); pc('\n'); return ;}
    while ((rev % 10) == 0) { count++; rev /= 10;} //obtain the count of the number of 0s
    rev = 0;
    while (N != 0) { rev = (rev<<3) + (rev<<1) + N % 10; N /= 10;}  //store reverse of N in rev
    while (rev != 0) { pc(rev % 10 + '0'); rev /= 10;}
    while (count--) pc('0');
}

int main() {
  int n;
  read(&n);
  int arr[n];
  for(int i = 0; i < n; i++) read(arr + i);
  for(int i = n; i --> 0;) writeMyNum(arr[i]), pc('\n');
}
