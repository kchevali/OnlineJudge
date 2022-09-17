#include <bits/stdc++.h>
using namespace std;
typedef long long l;

string toStr(l n, l base) {
    string convertString = "0123456789ABCDEF";
    if (n < base) {
        return string(1, convertString[n]); // converts char to string, and returns it
    } else {
        return toStr(n/base, base) + convertString[n%base]; // function makes a recursive call to itself.
    }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l t;
  cin >> t;
  for(l i = 0; i < t; i++){
    l k, b, n;
    cin >> k >> b >> n;
    string digits = toStr(n, b);
    l total = 0;
    for(char digit: digits){
      l value = digit < 'A' ? (digit - '0') : (digit - 'A' + 10);
      total += value * value;
    }
    cout << k << " " << total << "\n";
  }
}
