#include <bits/stdc++.h>
using namespace std;

// declared global variables to create array on heap
// allows larger arrays up to 1e8
// N is between 1e6 and 1e7 - based on assertions
const int N = 1e7, inf = 0x3f3f3f3f;
int parent[N], depth[N];
vector<int> adj[N];

// BFS: Unweighted - find path from one source
// Complexity O(V+E)
void bfs(int src, int dest) {
  queue<int> q;
  q.push(parent[src] = src);
  depth[src] = 0;

  while (!q.empty()) {
    int a = q.front();
    q.pop();
    for (int b : adj[a]) {
      if (parent[b] == -1) {
        parent[b] = a;
        depth[b] = depth[a] + 1;
        if (b == dest) return;
        q.push(b);
      }
    }
  }
}

// get path based on the parent of each node
int getPath(int src, int dest, int* pOutBuffer, int nOutBufferSize) {
  int length = depth[dest];
  for (int i = 0; src != dest && i < nOutBufferSize; i++) pOutBuffer[i] = dest, dest = parent[dest];
  std::reverse(pOutBuffer, pOutBuffer + min(length, nOutBufferSize));  // to start at src instead of dest
  return length;
}

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize) {
  int n = nMapWidth * nMapHeight;
  assert(n < N);

  // possible directions - move down & right (and inverse)
  int dx[2] = {0, 1}, dy[2] = {1, 0};

  // iterate every element in grid
  for (int i = 0, index = 0; i < nMapHeight; i++) {
    for (int j = 0; j < nMapWidth; j++, index++) {
      // check if node is walkable
      if (pMap[index] == 1) {
        // iterate directions to next node
        for (int k = 0; k < 2; k++) {
          int x = j + dx[k], y = i + dy[k], index2 = x + y * nMapWidth;
          // check bounds and next node is walkable
          if (x < nMapWidth && y < nMapHeight && pMap[index2] == 1) {  // x >= 0 && y >= 0 &&
            // add adj between nodes in both directions
            adj[index].push_back(index2);
            adj[index2].push_back(index);
          }
        }
      }
    }
  }

  int src = nStartX + nStartY * nMapWidth, dest = nTargetX + nTargetY * nMapWidth;
  memset(parent, -1, sizeof(int) * n);  // set parent of every node to -1
  bfs(src, dest);
  if (depth[dest] <= nOutBufferSize) {
    getPath(src, dest, pOutBuffer, nOutBufferSize);
  }
  // check if destination was visited
  return parent[dest] == -1 ? -1 : depth[dest];
}

// int main() {
//   unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
//   int pOutBuffer[12];
//   int length = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
//   for (int i = 0; i < length; i++) {
//     cout << pOutBuffer[i] << " ";
//   }
//   cout << "\n";

//   cout << length << "\n";
// }