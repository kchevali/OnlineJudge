/**
 * Kevin Chevalier
 * Algorithms
 * Spring 2019
 * General Description:
 * The objective of this file is to develop a C++ algorithm that can create a
 * minimum spanning tree of a set of coordinates. This means that I need to find
 * an effienct way to connect all of the points (or freckles as represented in
 * the problem) with the minimum amount "ink" in between them. In this file
 *  Kruskal's algorithm was used.
 */
#include <bits/stdc++.h>  //import all
// some useful shortcuts
#define PB emplace_back                       // append to vector
#define C cout <<                             // print
#define E << "\n"                             // new line for output
#define _ << " " <<                           // add space during output
#define gc getchar_unlocked                   // fast integer input
#define fpp(i, a, b) for (i = a; i < b; i++)  // concise forward for loop
#define dc(x) \
  cout << fixed << setprecision(x) <<  // fixed precision output of doubles
using namespace std;
typedef long long l;  // shorthand integer and vectors
typedef vector<l> vl;
typedef vector<vl> vvl;

/**
 * Gets next integer from input
 * Note: This method is part of my personal library and was originally taken
 * from the internet. It's a very fast io method that allows me to solve
 * problems with large input. The logic within the method does not contribute to
 * the general problem at hand, so it should be not considered for dishonest
 * work.  This problem did not contain large input, but the code was included
 * here for personal interest, practice and general consistency with my other
 * work.
 */
void read(l &x) {
  l c = gc();
  x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc())
    ;
  if (c == '-') {
    neg = 1;
    c = gc();
  }
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
  if (neg) x = -x;
}

/**
 * Gets the next output from input
 */
void readd(double &x) { scanf("%lf", &x); }

typedef double d;                // The datatype for the edge weight
typedef vector<pair<d, d>> vdd;  // data structure to store coordinates
typedef tuple<d, l, l> T;        // data structure to store edge
typedef vector<T> vT;            // 1D edge vector
typedef vector<vT> vvT;          // 2D edge vector
l h;
d x;
vT adjDis;  // 1D edge vector

/**
 * Gets the input and sets the number of input and the adjanency list
 */
void coordToDistanceAdj() {
  read(h);  // number of input
  vdd coords = vdd();
  d a, b;
  l i, j;
  fpp(i, 0, h) {
    readd(a);  // read 2 numbers per line
    readd(b);
    coords.PB(make_pair(a, b));  // hold all coordinates
  }
  adjDis = vT();  // build all edges
  fpp(i, 0, h) {
    fpp(j, 0, h) {
      if (i < j) {  // only calculate the distance once, instead of twice based
                    // on the symmetry of undirected graphs
        d da = coords[i].first - coords[j].first,
          db = coords[i].second - coords[j].second, dis;
        dis = sqrt(da * da + db * db);        // distance formula
        adjDis[i].PB(make_tuple(dis, i, j));  // create forward edge
        adjDis[j].PB(make_tuple(dis, j, i));  // create backward edge
      }
    }
  }
}

/*
 *Union find disjoint find root of a node.
 */
vl p, ranks;
l findSet(l i) {
  return p[i] == i ? i : p[i] = findSet(p[i]);
}  // optimization included where search results are stored

/*
 *check if both nodes have same root - return true
 */
bool isSameSet(l i, l j) { return findSet(i) == findSet(j); }

/*
 *join the sets of i and j
 */
void unionSet(l i, l j) {
  l x = findSet(i), y = findSet(j);
  if (x == y) return;
  if (ranks[x] > ranks[y])
    p[y] = x;
  else {
    p[x] = y;
    if (ranks[x] == ranks[y]) ranks[y]++;
  }
}
/**
 * Prim's MST Algorithm. Accepts a 2D array of edges/tuples. Tuple =
 * (weight,index of vertex a, index of vertex b).
 */
d kruskal_mst(vT &v, l n) {
  sort(v.begin(),
       v.end());  // sort array by weight so the min weight is iterated first
  d weight = 0;
  for (T e : v) {
    if (!isSameSet(get<1>(e), get<2>(e))) {  // only consider edges that connect
                                             // disconnected sets of vertices
      unionSet(get<1>(e), get<2>(e));        // join set
      weight += get<0>(e);                   // add weight
    }
  }
  return weight;
}

int main() {
  ios_base::sync_with_stdio(false);  // fast input
  cin.tie(NULL);                     // fast input

  l test, i;
  read(test);  // number of test case
  fpp(i, 0, test) {
    coordToDistanceAdj();  // get input

    p = vl(h);  // initialized Union find disjoint set
    ranks = vl(h, 0);
    iota(p.begin(), p.end(), 0);  // fills arrray from 0 to h-1

    dc(2) kruskal_mst(adjDis, h) E;  // outputs result with 2 decimal places
  }
}
