#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;

  unordered_set<l> nums;

  for(l i = 0; i < n; i++){
    l x;
    cin >> x;
    nums.insert(x);
  }

  for(l i = 1; i < n; i++){
    l x;
    cin >> x;
    nums.erase(x);
  }

  for(l num: nums){
    cout << num << "\n";
  }
}
