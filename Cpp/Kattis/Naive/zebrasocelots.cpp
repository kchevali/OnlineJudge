#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;

  l num = 0;
  for(l i = 0; i < n; i++){
    char ch;
    cin >> ch;
    num = (num << 1) + (ch == 'O');
  }
  cout << num << "\n";
}
