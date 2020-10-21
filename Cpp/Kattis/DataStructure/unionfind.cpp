#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;

// p - parent of an element

// 0 1 2 3 4 5
//= 1 3
//= 1 4
//= 4 5

// 0 1 2 1 4 5
// 0 1 2 1 1 5
// 0 1 2 1 1 4

vl p, ranks, setSize;
l numSets;  // the number of disjoint sets
l findSet(l i) { return p[i] == i ? i : p[i] = findSet(p[i]); }
// return true if element i and j are in the same set, return false otherwise
bool isSameSet(l i, l j) { return findSet(i) == findSet(j); }
// union two sets that contain element i and j
void unionSet(l i, l j) {
  l x = findSet(i), y = findSet(j);
  if (x == y) return;
  // ranks is used to keep the tree short
  if (ranks[x] > ranks[y]) {
    p[y] = x;
    setSize[x] += setSize[y];
  } else {
    p[x] = y;
    setSize[y] += setSize[x];
    if (ranks[x] == ranks[y]) ranks[y]++;
  }
}
// return the size of the set that contain element i
l sizeOfSet(l i) { return setSize[findSet(i)]; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, q;
  cin >> n >> q;

  p = vl(n);
  ranks = vl(n, 0);
  iota(p.begin(), p.end(), 0);
  setSize = vl(n, 0);

  for (l i = 0; i < q; i++) {
    char ch;
    l a, b;
    cin >> ch >> a >> b;

    if (ch == '?') {
      cout << (isSameSet(a, b) ? "yes" : "no") << "\n";
    } else {
      unionSet(a, b);
    }
  }
}
