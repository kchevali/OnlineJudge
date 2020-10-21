#include "../all.cpp"

// Min number of character edits, inserts, or deletions
// if a[i] == b[j]: No change
// if v[i][j] == v[i-1][j-1] + 1: set a[i] to b[j]
// if v[i][j] == v[i-1][j] + 1: delete a[i]
// if v[i][j] == v[i-1][j-1] + 1: insert b[j] to a[i]
l minEditDistance2(string a, string b, l i, l j, vvl &v) {
  if (i == -1) return j + 1;
  if (j == -1) return i + 1;
  if (v[i][j] >= 0) return v[i][j];
  return v[i][j] = a[i] == b[j] ? minEditDistance2(a, b, i - 1, j - 1, v)
                                : (min({minEditDistance2(a, b, i - 1, j, v),
                                        minEditDistance2(a, b, i - 1, j - 1, v),
                                        minEditDistance2(a, b, i, j - 1, v)}) +
                                   1);
}

l minEditDistance(string a, string b) {
  vvl v = vvl(a.size(), vl(b.size(), -1));
  return minEditDistance2(a, b, a.size() - 1, b.size() - 1, v);
}

int main() {
  C minEditDistance("abcdef", "azced") E;
  return 0;
}