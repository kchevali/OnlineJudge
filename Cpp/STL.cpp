#include "all.cpp"
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  const l len = 15;
  l nums[]{5, 3, 7, 4, 6, 4, 1000, 2, 1, 9, 2, 1, 9, -1, -6};
  vector<l> a = {2, 1, 9};
  vector<l> b = {0, 0, 0};

  auto print = [](int n) { std::cout << n << " "; };

  cout << all_of(nums, nums + len, [](l x) { return x > 0; }) << "\n";
  cout << any_of(a.begin(), a.end(), [](l x) { return x == 2; }) << "\n";
  cout << none_of(nums, nums + len, [](l x) { return x < 10; }) << "\n";
  for_each(nums, nums + len, print);
  cout << "\n";

  cout << *(find(nums, nums + len, 9) + 1) << "\n";
  cout << *(find_if(nums, nums + len, [](l x) { return x < 0; }) - 1) << "\n";
  cout << *(find_end(nums, nums + len, a.begin(), a.end()) - 1) << "\n";
  cout << *(find_first_of(nums, nums + len, a.begin(), a.end()) - 1) << "\n";
  cout << *(adjacent_find(nums, nums + len) - 1) << "\n";
  cout << count(nums, nums + len, 9) << "\n";
  cout << count_if(nums, nums + len, [](l x) { return x < 0; }) << "\n";
  cout << *(mismatch(nums, nums + len, b.begin()).first) << "\n";
  cout << equal(nums, nums + len, b.begin()) << "\n";
  cout << is_permutation(nums, nums + len, b.begin()) << "\n";
  cout << *search(nums, nums + len, a.begin(), a.end()) << "\n";
  cout << *(search_n(nums, nums + len, 2, 4) - 1) << "\n";
}
