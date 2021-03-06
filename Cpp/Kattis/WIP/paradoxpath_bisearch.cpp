// Kevin Chevalier
// FINAL BFS SUBMISSION
#include <bits/stdc++.h>
using namespace std;

// #define db(args...)                           \
//   {                                           \
//     string _s = #args;                        \
//     replace(_s.begin(), _s.end(), ' ', '\0'); \
//     replace(_s.begin(), _s.end(), ',', ' ');  \
//     stringstream _ss(_s);                     \
//     istream_iterator<string> _it(_ss);        \
//     err(_it, args);                           \
//     cerr << "\n";                             \
//   }
// void err(istream_iterator<string> it) {}
// template <typename T, typename... Args>
// void err(istream_iterator<string> it, T a, Args... args) {
//   cerr << *it << " = " << a << "   ";
//   err(++it, args...);
// }

// declared global variables to create array on heap
// allows larger arrays up to 1e8
// big speed up for consective runs
const int N = 1e7;
int depth[N], rDepth[N], child[N], parent[N], adj[N][4];
char vis[N], rVis[N], adjSize[N], runCount = 0;

int bfs(queue<int>& q, char* v, char* v2, int* d, int* d2, int* p) {
  int meet = -1, best = N, length = q.size();
  // db(best);
  while (length--) {
    int a = q.front();
    q.pop();
    if (v2[a] == runCount && d[a] + d2[a] < best) {
      meet = a;
      best = d[a] + d2[a];
      // db(meet, best);
    }
    for (int i = adjSize[a]; i-- > 0;) {
      int b = adj[a][i];
      if (v[b] != runCount) {  // visited node this run?
        // db(a, b);
        p[b] = a;
        d[b] = d[a] + 1;
        v[b] = runCount;  // set node to visited this run
        q.push(b);
      }
    }
  }
  return meet;
}

int bidir_search(int src, int dest) {
  queue<int> q1, q2;
  q1.push(parent[src] = src), q2.push(child[dest] = dest);
  vis[src] = runCount, rVis[dest] = runCount;
  depth[src] = 0, rDepth[dest] = 0;
  int meet = -1;
  while (!q1.empty() && (meet = bfs(q1, vis, rVis, depth, rDepth, parent)) == -1 && !q2.empty() && (meet = bfs(q2, rVis, vis, rDepth, depth, child)) == -1) {
  }
  return meet;
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
  int index = bidir_search(src, dest);
  // db(index);
  if (index == -1) return -1;
  int length = depth[index] + rDepth[index];
  // db(depth[index], rDepth[index]);
  if (length <= nOutBufferSize) {
    for (int i = depth[index], curr = index; i-- > 0; curr = parent[curr]) {
      pOutBuffer[i] = curr;
      // db(i, curr);
    }
    for (int i = depth[index], curr = child[index]; i < length; i++, curr = child[curr]) {
      pOutBuffer[i] = curr;
      // db(i, curr);
    }

    // int i = length - 1;
    // for (int curr = dest; curr != index; curr = child[curr]) pOutBuffer[i] = curr;
    // for (int curr = index; curr != src; curr = parent[curr]) pOutBuffer[i] = curr;
  }
  // return distance
  return length;
}

// int main() {
//   // nStartX,  nStartY,  nTargetX,  nTargetY, pMap,  nMapWidth,  nMapHeight,  pOutBuffer,  nOutBufferSize
//   int nStartX = 0, nStartY = 0;
//   int nTargetX = 3, nTargetY = 3;
//   int nMapWidth = 4, nMapHeight = 4;
//   const int nOutBufferSize = 12;

//   unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//   int pOutBuffer[nOutBufferSize];
//   int length = FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
//   // FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
//   // FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
//   // FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);

//   for (int i = 0, index = 0; i < nMapHeight; i++) {
//     for (int j = 0; j < nMapWidth; j++, index++) {
//       cout << (char)(pMap[index] + '0');
//     }
//     cout << "\n";
//   }

//   for (int i = 0; i < length; i++) {
//     cout << pOutBuffer[i] << " ";
//   }
//   cout << "\n";

//   cout << length << "\n";
// }