/**
 * Kevin Chevalier
 * Algorithms
 * Spring 2019
 * General Description:
 * The objective of this file is to develop a C++ algorithm that can create a
 * minimum spanning tree of a set of coordinates. This means that I need to find
 * an effienct way to connect all of the points (or freckles as represented in
 * the problem) with the minimum amount "ink" in between them. In this file
 *  Prim's algorithm was used.
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
// shorthand integer and vectors
typedef long long l;
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
typedef vector<bool> vb;
typedef priority_queue<T, vector<T>, greater<T>>
    pq;  // priority queue - min out first

l h;         // the number of lines of input
vvT adjDis;  // 2D edge vector as a adj list

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
  adjDis = vvT(h, vT());  // build all edges
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

/**
 * Prim's MST Algorithm. Accepts a 2D array of edges/tuples. Tuple =
 * (weight,index of vertex a, index of vertex b).
 */
d prim_mst() {
  d weight = 0;
  vb visited(adjDis.size(), false);
  pq q;

  // setup source node
  visited[0] = true;
  for (auto x : adjDis[0]) q.push(x);

  while (!q.empty()) {  // main loop
    auto t = q.top();   // extract edge based on min weight
    q.pop();

    d w = get<0>(t);                 // weight
    l a = get<1>(t), b = get<2>(t);  // vertices of edge
    if (!visited[b]) {               // continue if node is not visited yet
      weight += w;                   // add weight
      visited[b] = true;             // mark as visited
      for (auto x : adjDis[b]) {     // add all connected unvisited edges
        if (!visited[get<2>(x)]) q.push(x);
      }
    }
  }
  return weight;  // return MST
}

int main() {
  ios_base::sync_with_stdio(false);  // fast input
  cin.tie(NULL);                     // fast input

  l test, i;
  d a, b;
  read(test);  // number of test cases
  fpp(i, 0, test) {
    coordToDistanceAdj();  // get input
    dc(2) prim_mst() E;    // run prim and output result with 2 decimal places
  }
}
