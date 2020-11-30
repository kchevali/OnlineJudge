#include "../all.cpp"

const l n = 9;
l nums[n]{5, 3, 3, 2, 7, 5, 3, 8, 1};

void test(l x) {
  cout << "x = " << x << "\n";
  cout << "Contains: " << (binary_search(nums, nums + n, x) ? "True" : "False") << "\n";

  auto lower = lower_bound(nums, nums + n, x), upper = upper_bound(nums, nums + n, x);
  l lowerIndex = lower - nums, upperIndex = upper - nums;
  cout << "Lower index: " << lowerIndex << " Value: " << nums[lowerIndex] << "\n";
  cout << "Upper index: " << upperIndex << " Value: " << nums[upperIndex] << "\n\n";
}

// int main() {
//   sort(nums, nums + n);

//   cout << "NUMS:\n";
//   for (l num : nums) cout << num << " ";
//   cout << "\n";
//   for (l i = 0; i < n; i++) cout << i << " ";
//   cout << "\n\n";

//   l test_nums[5]{3, -1, 9, 4, 8};

//   for (l num : test_nums) test(num);
// }
/*
OUTPUT:
NUMS:
1 2 3 3 3 5 5 7 8
0 1 2 3 4 5 6 7 8

x = 3
Contains: True
Lower index: 2 Value: 3
Upper index: 5 Value: 5

x = -1
Contains: False
Lower index: 0 Value: 1
Upper index: 0 Value: 1

x = 9
Contains: False
Lower index: 9 Value: 0
Upper index: 9 Value: 0

x = 4
Contains: False
Lower index: 5 Value: 5
Upper index: 5 Value: 5

x = 8
Contains: True
Lower index: 8 Value: 8
Upper index: 9 Value: 0
*/

l* my_lower_bound(l* a, l* b, l t) {
  while (a < b) {
    l* m = a + (b - a) / 2;
    if (t <= *m)
      b = m;
    else
      a = m + 1;
  }
  return a;
}

l* my_upper_bound(l* a, l* b, l t) {
  while (a < b) {
    l* m = a + (b - a) / 2;
    if (t < *m)
      b = m;
    else
      a = m + 1;
  }
  return a;
}

int main() {
  sort(nums, nums + n);
  cout << "NUMS:\n";
  for (l num : nums) cout << num << " ";
  cout << "\n";

  l invalids[3]{0, 4, 9};

  for (l num : nums) {
    cout << num << " " << (my_lower_bound(nums, nums + n, num) == lower_bound(nums, nums + n, num) ? "PASS" : "FAIL") << "\n";
  }
  for (l num : invalids) {
    cout << num << " " << (my_lower_bound(nums, nums + n, num) == lower_bound(nums, nums + n, num) ? "PASS" : "FAIL") << "\n";
  }
}