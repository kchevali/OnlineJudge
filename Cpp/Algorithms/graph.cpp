#include "../all.cpp"

// IMPORTS:
// typedef vector<l> vl; typedef vector<vl> vvl;
// typedef pair<l, l> ll; typedef queue<l> ql;
// typedef vector<bool> vb;
// #define inf 0x3f3f3f3fLL
// #define xx first #define yy second

vl getPath(l dest, l pathLength, vl &prev) {
  vl path = vl(pathLength, 0);
  for (l i = pathLength - 1; i >= 0; i--) {
    path[i] = dest;
    dest = prev[dest];
  }
  return path;
}

// BFS: Unweighted - find path
// find path from single source
void bfs_single(l root, vector<vl> &adj, vl &prev, vl &depth) {
  queue<l> q;
  q.push(prev[root] = root);
  depth[root] = 1;  // init depth to inf
  while (!q.empty()) {
    l a = q.front();
    q.pop();
    for (l b : adj[a])
      if (depth[a] + 1 < depth[b]) {
        depth[b] = depth[a] + 1;
        prev[b] = a;
        q.push(b);
      }
  }
}

// find path from several sources
void bfs(vector<vl> &adj, vb isSource, vl &prev, vl &depth) {
  for (l i = 0; i < adj.size(); i++)
    if (isSource[i]) bfs_single(i, adj, prev, depth);
}

// const l N = 500 * 500 + 10;
l n, parent[N], rParent[N], depth[N], rDepth[N], maxLevel = inf;
vl adj[N], rAdj[N];

bool bidir_bfs(vl adj[N], queue<l> &q, l dest, l parent[N], l depth[N], l rDepth[N]) {
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
//   vl prev(n), depth(n, inf);

//   for (l i = 0; i < m; i++) {
//     l a, b;
//     cin >> a >> b;
//     adj[a].push_back(b);
//     adj[b].push_back(a);
//   }
//   bidir_search(adj, adj, 0, n - 1, prev, depth);
//   for (l i = 0; i < n; i++) {
//     cout << "\nDEPTH[" << i << "] = " << depth[i] << "\n";
//     cout << "PREV[" << i << "] = " << prev[i] << "\n";
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
// going from node a to b
// init depth at inf
// #define inf 0x3f3f3f3fLL
l maxDistIndex = 0;
void dfs_single(l a, l b, vector<vl> &adj, vl &prev, vl &depth) {
  prev[b] = a;
  depth[b] = depth[a] + 1;
  // if (depth[b] > depth[maxDistIndex]) maxDistIndex = b; //get tree diameter
  for (auto c : adj[b])
    if (depth[a] + 1 < depth[b]) dfs_single(b, c, adj, prev, depth);
}

void dfs(vector<vl> &adj, vb isSource, vl &prev, vl &depth) {
  for (l i = 0; i < adj.size(); i++)
    if (isSource[i]) dfs_single(i, i, adj, prev, depth);
}

// l maxDistIndex = 0;
void dfs_diameter(l a, vector<vl> &adj, vl &prev, vl &depth) {
  for (auto &b : adj[a]) {
    if (depth[a] + 1 < depth[b]) {
      prev[b] = a;
      depth[b] = depth[a] + 1;
      // cout << "DFS: " << a << " " << b << " D: " << depth[a] << " " << depth[b] << "\n";
      if (depth[b] > depth[maxDistIndex]) maxDistIndex = b;  // get tree diameter
      dfs_diameter(b, adj, prev, depth);
    }
  }
}

l get_tree_diameter(vector<vl> &adj) {
  vl prev(adj.size(), 0), depth(adj.size(), inf);
  depth[0] = 0;
  dfs_diameter(0, adj, prev, depth);
  // cout << "Greatest Depth: " << maxDistIndex << "\n";
  for (l i = 0; i < adj.size(); i++) depth[i] = inf;
  depth[maxDistIndex] = 0;
  dfs_diameter(maxDistIndex, adj, prev, depth);
  // cout << "Greatest Depth: " << maxDistIndex << "\n";
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

// Maximum Flow (Ford-Fulkerson Algorithm) O(VE2) - Undirected: One sink and
// source, non negative weights BFS Version:
bool bfsMod(l src, l dest, vector<vl> &resi, map<l, l> &parent) {
  vl vis(resi.size(), false);
  queue<l> q;
  q.push(src);
  vis[src] = true;
  while (!q.empty()) {
    l a = q.front();
    q.pop();
    for (l b = 0; b < resi.size(); b++) {
      if (!vis[b] && resi[a][b] > 0) {
        parent[b] = a;
        vis[b] = true;
        q.push(b);

        if (b == dest) return true;
      }
    }
  }
  return false;
}

// #define inf 0x3f3f3f3fLL
l bfsMaxFlow(l src, l dest, vector<vl> cap) {
  vector<vl> resi(cap.size(), vl(cap[0].size(), 0));
  for (l i = 0; i < cap.size(); i++) {
    for (l j = 0; j < cap[0].size(); j++) resi[i][j] = cap[i][j];
  }

  map<l, l> parent;
  vector<vl> augPath;  // Paths are stored here

  l maxFlow = 0;

  while (bfsMod(src, dest, resi, parent)) {
    vl augmentedPath;
    l flow = inf;

    l v = dest;
    while (v != src) {
      augmentedPath.push_back(v);
      l u = parent[v];
      flow = min(flow, resi[u][v]);
      v = u;
    }
    augmentedPath.push_back(src);
    reverse(augmentedPath.begin(), augmentedPath.end());
    augPath.push_back(augmentedPath);

    maxFlow += flow;

    v = dest;
    while (v != src) {
      l u = parent[v];
      resi[u][v] -= flow;
      resi[v][u] += flow;
      v = u;
    }
  }
  return maxFlow;
}

// DFS Version : (This is faster than BFS version if it is used to solve
// bipartite matching problem)

//   //cap - store the capacity. cap[i][j] - capacity i -> j
//   //res - store the result
//   //cap has to be pre-cominserted before calling flow method

// adjacent list, this is used when there are large number of vertex,
// but small number of edges connected to each vertex

// return the maximum flow
// typedef vector<bool> vb;
l dfsMod(l src, l dest, l minimum, vvl &cap, vvl &ans, vvl &adj, vb &vis) {
  // If sink has been reached, terminate
  if (src == dest) return minimum;

  vis[src] = true;
  for (l i : adj[src]) {
    if (cap[src][i] > 0 && !vis[i]) {
      l v = dfsMod(i, dest, min(minimum, cap[src][i]), cap, ans, adj, vis);
      if (v > 0) {
        cap[src][i] -= v;
        ans[src][i] += v;
        cap[i][src] += v;
        ans[i][src] -= v;
        return v;
      }
    }
  }
  // The sink has not been found.
  return 0;
}
l dfsMaxFlow(l src, l dest, vvl cap) {
  // Visited array to perform DFS, initially empty
  vb vis(cap.size(), false);

  // initialize adjacent list
  vvl adj(cap.size(), vl(cap.size(), 0));
  vvl ans(cap.size(), vl(cap.size(), 0));

  for (l i = 0; i < cap.size(); i++) {
    for (l j = 0; i < cap.size(); j++) {
      if (cap[i][j] > 0) {
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    }
  }

  l maxflow = 0, flow = 0;
  // Repeat until there is no path
  while ((flow = dfsMod(src, dest, inf, cap, ans, adj, vis)) > 0) {
    fill(vis.begin(), vis.end(), false);
    maxflow += flow;
  }

  return maxflow;
}

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

const l N = 10001;
vll adj[N];
l dist[N];
bool vis[N];

void dijkstra(l source, l n) {
  for (l i = 0; i < n; i++) {
    dist[i] = inf;
    vis[i] = 0;
  }
  priority_queue<ll, vll, greater<ll> > pq;  // w, node
  pq.push(make_pair(dist[source] = 0, source));
  while (!pq.empty()) {
    ll curr = pq.top();
    pq.pop();
    l a = curr.second;
    if (vis[a]) continue;
    vis[a] = true;
    for (l i = 0; i < adj[a].size(); i++) {
      l b = adj[a][i].second, w = adj[a][i].first;
      if (!vis[b] && w + dist[a] < dist[b]) {
        pq.push(make_pair((dist[b] = w + dist[a]), b));
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
// l dist[N];
bool isNeg[N];

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
void bellmanFord(l src, l n) {
  for (l i = 0; i < n; i++) {
    dist[i] = inf;
    isNeg[i] = false;
  }
  dist[src] = 0;

  for (l i = 1; i < n; i++)
    for (l a = 0; a < n; a++)
      if (dist[a] != inf)
        for (l j = 0; j < adj[a].size(); j++) {
          l b = adj[a][j].second;
          l w = adj[a][j].first;
          dist[b] = min(dist[a] + w, dist[b]);
        }

  bool isDone = false;
  while (!isDone) {
    isDone = true;
    for (l a = 0; a < n; a++) {
      if (dist[a] == inf) continue;
      for (l i = 0; i < adj[a].size(); i++) {
        l b = adj[a][i].second;
        l w = adj[a][i].first;
        if (dist[a] + w < dist[b] && !isNeg[b]) {
          isNeg[b] = true;
          isDone = false;
          dist[b] = -inf;
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
//                         : dist[q] == inf ? "Impossible" :
//                         to_string(dist[q]))
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