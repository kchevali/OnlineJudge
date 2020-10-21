#include <bits/stdc++.h>
using namespace std;
typedef long long l;
#define linf 0x3f3f3f3f3f3f3f3f

typedef ll ll;
typedef vector<l> vl;
typedef ll ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef queue<l> Q;  // min out
typedef vector<bool> vb;

const l sz = 10001;  // Maximum possible number of vertices. Preallocating space
                     // for DataStructures accordingly
vector<ll> a[sz];    // Adjacency list
l dis[sz];           // Stores shortest distance
bool vis[sz] = {0};  // Determines whether the node has been visited or not

void dijkstra(l source, l n)  // Algorithm for SSSP
{
  for (l i = 0; i < sz; i++)  // Set initial distances to Infinity
    dis[i] = linf;
  // Custom Comparator for Determining priority for priority queue (shortest
  // edge comes first)
  class prioritize {
   public:
    bool operator()(ll& p1, ll& p2) { return p1.second > p2.second; }
  };
  priority_queue<ll, vector<ll>, prioritize> pq;
  // Priority queue to store vertex,weight pairs
  pq.push(make_pair(source, dis[source] = 0));
  // Pushing the source with distance from itself as 0
  while (!pq.empty()) {
    ll curr = pq.top();
    // Current vertex. The shortest distance for
    // this has been found
    pq.pop();
    l cv = curr.first, cw = curr.second;
    //'cw' the final shortest distance for this vertex
    if (vis[cv]) continue;
    // If the vertex is already visited, no pol in exploring
    // adjacent vertices
    vis[cv] = true;
    for (l i = 0; i < a[cv].size(); i++)
      // Iterating through all adjacent vertices
      if (!vis[a[cv][i].first] && a[cv][i].second + cw < dis[a[cv][i].first])
        // If this node is not visited and the current parent node
        // distance+distance from there to this node is shorted than the initial
        // distace set to this node, update it
        pq.push(make_pair(a[cv][i].first,
                          (dis[a[cv][i].first] = a[cv][i].second + cw)));
    // Set the new distance and add to priority queue
  }
}

int main()  // Driver Function for dijkstra SSSP
{
  l n, m, x, y, w;  // Number of vertices and edges
  // cout<<"Enter number of vertices and edges in the graph\n";
  cin >> n >> m;
  for (l i = 0; i < m; i++)  // Building Graph
  {
    cin >> x >> y >> w;  // Vertex1, Vertex2, weight of edge
    a[x].push_back(make_pair(y, w));
    a[y].push_back(make_pair(x, w));
  }
  // cout<<"Enter source for dijkstra's SSSP algorithm\n";
  l source;
  cin >> source;
  dijkstra(source, n);
  // SSSP from source (Also passing number of vertices as parameter)
  cout << "Source is: " << source
       << ". The shortest distance to every other vertex from here is: \n";
  for (l i = 1; i <= n; i++)  // Prling final shortest distances from source
  {
    cout << "Vertex: " << i << " , Distance: ";
    dis[i] != linf ? cout << dis[i] << "\n" : cout << "-1\n";
  }
  return 0;
}