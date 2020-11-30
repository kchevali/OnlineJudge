#include "../all.cpp"

// Global variables
const l N = 1e2;
l maxLevel = inf, maxDistIndex = 0;
l parent[N], rParent[N], path[N], depth[N], rDepth[N], resi[N][N], cap[N][N];
vector<l> adj[N], rAdj[N];
vector<pair<l, l>> pAdj[N];
bool vis[N], isNeg[N];
typedef tuple<int, l, l> edge;  // weight, a, b

// Function: get path from parent[]
// l path[N];

// Complexity: O(n)
void getPath(l dest, l pathLength) {
  for (l i = pathLength - 1; i >= 0; i--) {
    path[i] = dest;
    dest = parent[dest];
  }
}

// Function: Unweighted - find path from one source
// const l N = 1e4, inf = 0x3f3f3f3f3f3f3f3f;
// l parent[N], depth[N];
// vector<l> adj[N];
// Main: memset(depth,0x3f,sizeof(depth));for (l j = 0; j < n; j++) adj[j] = vl();
// Complexity O(V+E)
void bfs(l src) {
  queue<l> q;
  q.push(parent[src] = src);
  // depth = unordered_map<l, l>();//for freq depth reset use unordered_map
  depth[src] = 1;  // init depth to inf
  while (!q.empty()) {
    l a = q.front();
    q.pop();
    for (l b : adj[a]) {
      if (depth[a] + 1 < depth[b]) {
        depth[b] = depth[a] + 1;
        parent[b] = a;
        q.push(b);
      }
    }
  }
}

// const l N = 1e5, inf = 1e18;
// l parent[N], rParent[N], depth[N], rDepth[N], maxLevel = inf;
// vl adj[N], rAdj[N];

bool bidir_bfs(vector<l> adj[N], queue<l> &q, l dest, l parent[N], l depth[N], l rDepth[N]) {
  l a = q.front();
  q.pop();
  if (depth[a] > maxLevel) return false;
  for (l b : adj[a]) {
    if (depth[a] + 1 < depth[b]) {
      depth[b] = depth[a] + 1;
      if (depth[b] + rDepth[b] < depth[dest]) {
        maxLevel = max(depth[b], rDepth[b]);
        depth[dest] = depth[b] + rDepth[b];
      }
      parent[b] = a;
      q.push(b);
    }
  }
  return true;
}  // a <- b <- c <- d <- e <- f

// init depth to inf
void bidir_search(l src, l dest) {
  queue<l> q1, q2;
  q1.push(parent[src] = src);
  depth[src] = 1;  // must be >= 0
  q2.push(rParent[dest] = dest);
  rDepth[dest] = -1;  // must be < 0
  while (!q1.empty() && bidir_bfs(adj, q1, dest, parent, depth, rDepth) && !q2.empty() && bidir_bfs(rAdj, q2, dest, rParent, rDepth, depth)) {
  }
}

// int main() {
//   ios_base::sync_with_stdio(false);
//   cin.tie(NULL);

//   l n, m;
//   cin >> n >> m;

//   vector<vl> adj(n);
//   vl parent(n), depth(n, inf);

//   for (l i = 0; i < m; i++) {
//     l a, b;
//     cin >> a >> b;
//     adj[a].push_back(b);
//     adj[b].push_back(a);
//   }
//   bidir_search(adj, adj, 0, n - 1, parent, depth);
//   for (l i = 0; i < n; i++) {
//     cout << "\nDEPTH[" << i << "] = " << depth[i] << "\n";
//     cout << "PREV[" << i << "] = " << parent[i] << "\n";
//   }
// }

/*
6 5
0 1
1 2
2 3
3 4
4 5

15 14
0 4
1 4
2 5
3 5
4 6
5 6
6 7
7 8
8 9
8 10
9 11
9 12
10 13
10 14

*/
// DFS - Returns order that finish all children
// TREE DIAMETER - may be weighted(change depth calc)
// const l N = 1e4, inf = 0x3f3f3f3f3f3f3f3f;
// l parent[N], depth[N];
// vector<l> adj[N];
// Main: memset(depth,0x3f,sizeof(depth));for (l j = 0; j < n; j++) adj[j] = vl();
// Complexity O(V+E)
void dfs(l src) {  // insert for tree diameter
  // depth = unordered_map<l, l>();//for freq depth reset use unordered_map, not memset
  depth[src] = 0;
  stack<l> st;
  st.push(src);
  while (!st.empty()) {
    l a = st.top();
    st.pop();
    for (auto &b : adj[a]) {
      if (depth[a] + 1 < depth[b]) {
        parent[b] = a;
        depth[b] = depth[a] + 1;
        // if (depth[b] > depth[maxDistIndex]) maxDistIndex = b;  // get tree diameter
        st.push(b);
      }
    }
  }
}
void dfs(l src, l &maxDistIndex);  // update above for tree diameter

l get_tree_diameter(l src) {
  l maxDistIndex = src;
  dfs(src, maxDistIndex);
  dfs(maxDistIndex, maxDistIndex);
  return depth[maxDistIndex];
}
// int main() {
//   l n, m, i;
//   cin >> n >> m;
//   vector<vl> adj(n, vl());
//   fpp(i, 0, m) {
//     l a, b;
//     cin >> a >> b;
//     adj[a].push_back(b);
//     adj[b].push_back(a);
//   }
//   auto path = bfs(0, n - 1, adj);
//   cout << path.size() << endl;
//   while (!path.empty()) {
//     cout << path.top() << " ";
//     path.pop();
//   }
//   cout << endl;
//   return 0;
// }

// Max Flow
// typedef tuple<int, l, l> edge;  // weight, a, b
// typedef vector<l> vl;
// typedef pair<l,l> ll;
// const l inf = 1e18;

class MaxFlow {
 public:
  MaxFlow(l nodes) : n(nodes) {
    edges.clear();
    adj.assign(n, vl());
  }

  // directed means one way edge
  void addEdge(l a, l b, l w, bool directed = true) {
    if (a == b) return;
    edges.emplace_back(b, w, 0);
    adj[a].push_back(edges.size() - 1);
    edges.emplace_back(a, directed ? 0 : w, 0);
    adj[b].push_back(edges.size() - 1);
  }

  // Complexity: O(V*E^2) - SLOWER
  l edmondsKarp(l s, l t) {
    l mf = 0;
    while (bfs(s, t)) {
      l f = sendOneFlow(s, t);
      if (f == 0) break;
      mf += f;
    }
    return mf;
  }
  // Complexity: O(V^2*E) - FASTER (V<E)
  l dinic(l s, l t) {
    l mf = 0;
    while (bfs(s, t)) {
      last.assign(n, 0);
      while (l f = dfs(s, t)) mf += f;
    }
    return mf;
  }

 private:
  bool bfs(l src, l dest) {
    d.assign(n, -1);
    d[src] = 0;
    queue<l> q({src});
    p.assign(n, {-1, -1});
    while (!q.empty()) {
      l a = q.front();
      q.pop();
      if (a == dest) break;
      for (auto &idx : adj[a]) {
        auto &[b, cap, flow] = edges[idx];
        if ((cap - flow > 0) && (d[b] == -1)) d[b] = d[a] + 1, q.push(b), p[b] = {a, idx};
      }
    }
    return d[dest] != -1;
  }

  l dfs(l a, l dest, l f = inf) {
    if ((a == dest) || (f == 0)) return f;
    for (l &i = last[a]; i < (l)adj[a].size(); i++) {
      auto &[b, cap, flow] = edges[adj[a][i]];
      if (d[b] != d[a] + 1) continue;
      if (l pushed = dfs(b, dest, min(f, cap - flow))) {
        flow += pushed;
        auto &rflow = get<2>(edges[adj[a][i] ^ 1]);
        rflow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  l sendOneFlow(l src, l dest, l f = inf) {
    if (src == dest) return f;
    auto &[a, idx] = p[dest];
    auto &cap = get<1>(edges[idx]), &flow = get<2>(edges[idx]);
    l pushed = sendOneFlow(src, a, min(f, cap - flow));
    flow += pushed;
    auto &rflow = get<2>(edges[idx ^ 1]);
    rflow -= pushed;
    return pushed;
  }

  l n;
  vector<edge> edges;
  vector<vl> adj;
  vl d, last;
  vector<ll> p;
};

// int main() {
//   vector<vl> cap(4, vl(4, 0));
//   cap[0][1] = 10;
//   cap[0][2] = 5;
//   cap[1][2] = 1;
//   cap[1][3] = 3;
//   cap[2][3] = 5;

//   cout << bfsMaxFlow(0, 3, cap) << endl;
//   cout << dfsMaxFlow(0, 3, cap) << endl;
//   cout << "Done!" << endl;
//   return 0;
// }

// #define inf 0x3f3f3f3fLL

// typedef pair<l, l> ll;
// typedef vector<l> vl;
// typedef vector<ll> vll;

// const l N = 10001;
// vector<pair<l,>> pAdj[N];
// l depth[N];
// bool vis[N];

void dijkstra(l source, l n) {
  for (l i = 0; i < n; i++) {
    depth[i] = inf;
    vis[i] = 0;
  }
  priority_queue<ll, vll, greater<ll>> pq;  // w, node
  pq.push(make_pair(depth[source] = 0, source));
  while (!pq.empty()) {
    ll curr = pq.top();
    pq.pop();
    l a = curr.second;
    if (vis[a]) continue;
    vis[a] = true;
    for (l i = 0; i < adj[a].size(); i++) {
      l b = pAdj[a][i].second, w = pAdj[a][i].first;
      if (!vis[b] && w + depth[a] < depth[b]) {
        pq.push(make_pair((depth[b] = w + depth[a]), b));
      }
    }
  }
}

// int main() {
//   l n, m, q, s;
//   l x, y, w;
//   while (true) {
//     cin >> n >> m >> q >> s;
//     if (n == 0 && m == 0 && q == 0 && s == 0) break;
//     for (l i = 0; i < n; i++) adj[i] = vll();
//     for (l i = 0; i < m; i++) {
//       cin >> x >> y >> w;
//       adj[x].push_back(make_pair(w, y));
//     }
//     dijkstra(s, n);
//     for (l i = 0; i < q; i++) {
//       l num;
//       cin >> num;
//       if (dis[num] >= inf)
//         printf("Impossible\n");
//       else
//         printf("%lld\n", dis[num]);
//     }
//     cout << "\n";
//   }

// const l N = 1001;
// vll adj[N];
// l depth[N];
// bool isNeg[N];

// The main function that finds shortest depthances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
void bellmanFord(l src, l n) {
  for (l i = 0; i < n; i++) {
    depth[i] = inf;
    isNeg[i] = false;
  }
  depth[src] = 0;

  for (l i = 1; i < n; i++)
    for (l a = 0; a < n; a++)
      if (depth[a] != inf)
        for (l j = 0; j < adj[a].size(); j++) {
          l b = pAdj[a][j].second;
          l w = pAdj[a][j].first;
          depth[b] = min(depth[a] + w, depth[b]);
        }

  bool isDone = false;
  while (!isDone) {
    isDone = true;
    for (l a = 0; a < n; a++) {
      if (depth[a] == inf) continue;
      for (l i = 0; i < adj[a].size(); i++) {
        l b = pAdj[a][i].second;
        l w = pAdj[a][i].first;
        if (depth[a] + w < depth[b] && !isNeg[b]) {
          isNeg[b] = true;
          isDone = false;
          depth[b] = -inf;
        }
      }
    }
  }
}

// int main() {
//   ios_base::sync_with_stdio(false);
//   cin.tie(NULL);

//   while (true) {
//     l n, m, qs, s;
//     cin >> n >> m >> qs >> s;
//     if (n == 0 && m == 0 && qs == 0 && s == 0) break;
//     for (l i = 0; i < n; i++) adj[i] = vll();
//     for (l i = 0; i < m; i++) {
//       l a, b, w;
//       cin >> a >> b >> w;
//       adj[a].emplace_back(make_pair(w, b));
//     }
//     bellmanFord(s, n);
//     for (l i = 0; i < qs; i++) {
//       l q;
//       cin >> q;
//       cout << (isNeg[q] ? "-Infinity"
//                         : depth[q] == inf ? "Impossible" :
//                         to_string(depth[q]))
//            << "\n";
//     }
//     cout << "\n";
//   }
// }

// Tarjan's Strongly Connected Component
// Cycle detection //O(V+E)

// supporting
void dfsSCC(l &a, vl *adj, stack<l> &st, l *onStack, l *ids, l *low, l &id, l &counter) {
  st.push(a);
  onStack[a] = true;
  ids[a] = low[a] = id++;
  for (auto &b : adj[a]) {
    if (ids[b] == -1) dfsSCC(b, adj, st, onStack, ids, low, id, counter);
    if (onStack[b]) low[a] = min(low[a], low[b]);
  }
  if (ids[a] == low[a]) {
    l c;
    do {
      c = st.top();
      st.pop();
      onStack[c] = false;
      low[c] = ids[a];
    } while (c != a);
    counter++;
  }
}
// main - low -> uninit array[n]
l SCC(vl *adj, l n, l *low) {
  l id = 0, counter = 0;
  l ids[n], onStack[n];
  stack<l> st;
  for (l i = 0; i < n; i++) {
    ids[i] = -1;
    onStack[i] = false;
  }
  for (l i = 0; i < n; i++)
    if (ids[i] == -1) dfsSCC(i, adj, st, onStack, ids, low, id, counter);
  return counter;
}

// All Pair Shortest Path (APSP Floyd Warshall’s Algorithm)
// Accepts negative weights
// Complexity: O(N^3)
l depNN[N][N];
void APSP(l n) {
  for (l k = 0; k < n; k++)
    for (l i = 0; i < n; i++)
      for (l j = 0; j < n; j++)
        if (depNN[i][k] != inf && depNN[k][j] != inf) depNN[i][j] = min(depNN[i][j], depNN[i][k] + depNN[k][j]);
}

int main() {
  // example that treats neg weight as inf
  l n;
  cin >> n;
  for (l i = 0; i < n; i++) {
    for (l j = 0; j < n; j++) {
      scanf("%lld", &depNN[i][j]);
      if (depNN[i][j] < 0) depNN[i][j] = inf;
    }
  }

  APSP(n);
  for (l i = 0; i < n; i++) {
    for (l j = 0; j < n; j++) {
      cout << depNN[i][j] << " ";
    }
    cout << "\n";
  }
}

/*
All Pair Shortest Path
7
0 3 6 -1 -1 -1 -1
3 0 2 1 -1 -1 -1
6 2 0 1 4 2 -1
-1 1 1 0 2 -1 4
-1 -1 4 2 0 2 1
-1 -1 2 -1 2 0 1
-1 -1 -1 4 1 1 0
https://www.tutorialspoint.com/all-pairs-shortest-paths

Solution:
0 3 4 5 6 7 7
3 0 2 1 3 4 4
4 2 0 1 3 2 3
5 1 1 0 2 3 3
6 3 3 2 0 2 1
7 4 2 3 2 0 1
7 4 3 3 1 1 0
*/