#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  l arr[n-1];
  for(l i = 1; i < n; i++){
    l x;
    cin >> x;
    arr[x] = i + 1;
  }
  cout << 1;
  for(l i = 1; i < n; i++)cout << " " << arr[i - 1];
  cout << "\n";
}
