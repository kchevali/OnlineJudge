// Set Algorithms
//================================================================================================================================================
// Union-Find Disjoint Set
// This type of problems involving commands like union two sets multiple times,
// and then have multiple queries about the size of the set, total number of
// sets, or are two elements in the same set. (If there is only one query, then
// DFS is enough: by looking each element as a vertex, then union two element is
// simply push_back an edge between two vertices. This is still slower then
// Union-Find data structure, but easier to implement)

#include "../all.cpp"

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

// INCLUDE IN MAIN
// p = vl(n);
// ranks = vl(n, 0);
// iota(p.begin(), p.end(), 0);
// setSize = vl(n, 0);

//================================================================================================================================================
