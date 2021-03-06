// Kevin Chevalier
// FINAL BFS SUBMISSION
#include <bits/stdc++.h>
using namespace std;

// declared global variables to create array on heap
// allows larger arrays up to 1e8
// big speed up for consective runs
const int N = 1e7;
int depth[N], parent[N], adj[N][4];
char vis[N], adjSize[N], runCount = 0;

// BFS: Unweighted - find path from one source
// Complexity O(V+E)
void bfs(int src, int dest) {
  parent[src] = src;
  depth[src] = 0;
  vis[src] = runCount;  // visited src this run

  queue<int> q;
  q.push(src);
  while (!q.empty()) {
    int a = q.front();
    q.pop();
    for (int i = adjSize[a]; i-- > 0;) {
      int b = adj[a][i];
      if (vis[b] != runCount) {  // visited node this run?
        parent[b] = a;
        depth[b] = depth[a] + 1;
        vis[b] = runCount;      // set node to visited this run
        if (b == dest) return;  // terminate when find dest first
        q.push(b);
      }
    }
  }
}

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize) {
  // Starts new run here
  if (runCount++ == 0) memset(vis, 0, sizeof(char) * N);  // set all nodes to not visited strictly only once
  int n = nMapWidth * nMapHeight;                         // number of nodes

  // possible directions - move down & right (and inverse)
  int dx[2] = {0, 1}, dy[2] = {1, 0};

  memset(adjSize, 0, sizeof(char) * n);  // number of adjacent nodes is reset to 0

  // iterate every element in grid
  for (int i = 0, index = 0; i < nMapHeight; i++) {
    for (int j = 0; j < nMapWidth; j++, index++) {
      // check if node is walkable
      if (pMap[index] == 1) {
        // iterate directions to next node
        for (int k = 0; k < 2; k++) {
          int x = j + dx[k], y = i + dy[k], index2 = x + y * nMapWidth;

          // check bounds and that next node is walkable
          if (x < nMapWidth && y < nMapHeight && pMap[index2] == 1) {
            adj[index][adjSize[index]++] = index2;
            adj[index2][adjSize[index2]++] = index;
          }
        }
      }
    }
  }
  int src = nStartX + nStartY * nMapWidth, dest = nTargetX + nTargetY * nMapWidth;
  bfs(src, dest);
  if (vis[dest] != runCount) return -1;  // haven't seen destination this run
  if (depth[dest] <= nOutBufferSize) {   // find path
    for (int i = depth[dest], curr = dest; i-- > 0; curr = parent[curr]) pOutBuffer[i] = curr;
  }
  // return distance
  return depth[dest];
}
