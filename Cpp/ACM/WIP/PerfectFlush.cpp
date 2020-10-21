#include <bits/stdc++.h>

using namespace std;
typedef long long l;
typedef vector<l> vl;

// set with insertion order
// restrictions: cannot remove last inserted item
// complexity O(1) for insertion, removal and contains
class OrderedSet {
 public:
  OrderedSet(l maxValue) {
    nextArray = new l[maxValue + 1];
    prevArray = new l[maxValue + 1];
    indices = new l[maxValue + 1];
    for (l i = 0; i <= maxValue; i++) {
      prevArray[i] = nextArray[i] = indices[i] = -1;
    }
    prev = -1;
    this->maxValue = maxValue;
  }

  void insert(l x) {
    if (contains(x)) {
      if (!erase(x)) return;
    }

    // has previous
    if (prev != -1) {
      nextArray[prev] = x;
      prevArray[x] = prev;
    }
    prev = x;
    seq.emplace_back(x);
    indices[x] = seq.size() - 1;
  }

  bool erase(l x) {
    if (prev == x) {
      return false;
    }
    l prevItem = prevArray[x], nextItem = nextArray[x];
    if (prevItem != -1) {
      nextArray[prevItem] = nextItem;
    }

    if (nextItem != -1) {
      prevArray[nextItem] = prevItem;
    }
    prevArray[x] = -1;
    nextArray[x] = -1;
    seq[indices[x]] = -1;
    indices[x] = -1;

    return true;
  }

  bool contains(l x) { return indices[x] != -1; }

  l next(l x) { return nextArray[x]; }

  l getIndex(l x) { return indices[x]; }

  virtual ~OrderedSet() {
    delete[] nextArray;
    delete[] prevArray;
  }
  vl seq;

 private:
  l *nextArray, *prevArray, *indices;
  l prev, maxValue;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, k;
  cin >> n >> k;
  l nums[n];

  for (auto& num : nums) {
    cin >> num;
    num--;
  }

  bool runAgain = true;
  while (runAgain) {
    runAgain = false;
    // cout << "\nLoop\n";

    OrderedSet seq(k);
    for (l i = 0; i < n; i++) {
      l num = nums[i];
      if (num >= 0) {
        // cout << "\nNum: " << (num + 1) << "\n";

        if (!seq.contains(num)) {
          // haven't seen this num before
          // cout << "Not Seen: Inserting " << (num + 1) << "\n";
          seq.insert(num);

        } else {
          // have seen it before
          l next = seq.next(num);

          // check if next item exists
          if (next != -1) {
            // cout << "Comparing: " << (num + 1) << " w/ " << (next + 1) <<
            // "\n";
            if (num > next) {
              // cout << "Seen: Inserting " << (num + 1) << "\n";
              nums[seq.getIndex(num)] = -1;
              // cout << "Setting index: " << seq.getIndex(num) << " to -1\n";
              seq.insert(num);

              runAgain = true;
            }
            // else {
            //   cout << "No Action\n";
            // }
          }
          // else {
          //   cout << "Last ITEM\n";
          // }
        }
      }
    }
    if (!runAgain) {
      for (auto num : seq.seq) {
        if (num >= 0) cout << (num + 1) << " ";
      }
      cout << "\n";
    }
  }
}

// 5 3 3 2 1 3 2
// 1 3 2
// 6 4 3 4 1 3 4 2
// 1 3 4 2
// 5 3 2 3 1 2 3
// 1 2 3
// 8 3 3 2 1 3 2
// 1 3 2
// 21 3 3 3 2 1 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3
// 5 3 3 3 2 1 2