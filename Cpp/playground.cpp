#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

int main() {
  int nums[4] = {10, 20, 40, 80};
  int a = 0;
  nums[a] = a;
  for (int num : nums) {
    cout << num << "\n";
  }
}