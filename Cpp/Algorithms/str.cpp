#include <string>
#include <vector>

// Min number of character edits, inserts, or deletions
namespace minEditDistance {

  using l = long long;
  using Nums = std::vector<l>;
  using NumMatrix = std::vector<Nums>;

  // if a[i] == b[j]: No change
  // if v[i][j] == v[i-1][j-1] + 1: set a[i] to b[j]
  // if v[i][j] == v[i-1][j] + 1: delete a[i]
  // if v[i][j] == v[i-1][j-1] + 1: insert b[j] to a[i]
  l helper(std::string a, std::string b, l i, l j, NumMatrix &v) {
    if (i == -1) return j + 1;
    if (j == -1) return i + 1;
    if (v[i][j] >= 0) return v[i][j];
    return v[i][j] = a[i] == b[j] ?
      helper(a, b, i - 1, j - 1, v) : (
        std::min({
          helper(a, b, i - 1, j, v),
          helper(a, b, i - 1, j - 1, v),
          helper(a, b, i, j - 1, v)
        }) + 1);
  }

  l solve(std::string a, std::string b) {
    NumMatrix v(a.length(), Nums(b.length(), -1));
    return helper(a, b, a.length() - 1, b.length() - 1, v);
  }
}

#include <iostream>
int main() {
  std::cout << minEditDistance::solve("abcdef", "azced") << "\n";
  return 0;
}