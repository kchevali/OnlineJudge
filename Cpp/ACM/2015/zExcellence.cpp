
#include "../all.cpp"  //54 min
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  read(n);
  l i, j;
  vl nums(n);
  fpp(i, 0, n) read(nums[i]);
  sort(nums.begin(), nums.end());
  j = n - 1;
  l low = 100000000000LL;
  fpp(i, 0, n / 2) {
    low = min(low, nums[i] + nums[j]);

    j--;
  }
  cout << low << "\n";
}
