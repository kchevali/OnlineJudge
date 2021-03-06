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

typedef pair<int, int> ii;
typedef vector<ii> vii;
const int N = 1e7, inf = 0x3f3f3f3f;
int depth[N], parent[N], heu[N], adj[N][4];
char vis[N], adjSize[N], runCount = 0;

// Complexity: O(V + E*log(V))
void aStar(int src, int dest) {
  priority_queue<ii, vii, greater<ii>> pq;  // w, node
  pq.push(make_pair(depth[src] = 0, parent[src] = src));
  while (!pq.empty()) {
    auto [h, a] = pq.top();
    pq.pop();
    // db(a, h);

    if (a == dest) {
      vis[a] = runCount;
      return;
    }
    if (vis[a] == runCount) continue;
    vis[a] = runCount;
    // db(a, h)

    for (int i = adjSize[a]; i-- > 0;) {
      int b = adj[a][i];
      // db(a, b);
      if (vis[b] != runCount && depth[a] + 1 < depth[b]) {
        parent[b] = a, depth[b] = depth[a] + 1;
        pq.push(make_pair(heu[b] + depth[a], b));
      }
    }
  }
}

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize) {
  if (runCount++ == 0) memset(vis, 0, sizeof(char) * N);
  int n = nMapWidth * nMapHeight;  // number of nodes

  // possible directions - move down & right (and inverse)
  int dx[2] = {0, 1}, dy[2] = {1, 0};

  memset(adjSize, 0, sizeof(char) * n);  // number of adjacent nodes is reset to 0
  // memset(vis, 0, sizeof(bool) * n);
  memset(depth, 0x3f, sizeof(int) * n);

  // iterate every element in grid
  for (int i = 0, index = 0; i < nMapHeight; i++) {
    for (int j = 0; j < nMapWidth; j++, index++) {
      // check if node is walkable
      if (pMap[index] == 1) {
        heu[index] = abs(i - nTargetY) + abs(j - nTargetX);
        // db(index, heu[index]);
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
  aStar(src, dest);
  if (vis[dest] != runCount) return -1;
  if (depth[dest] <= nOutBufferSize) {
    for (int i = depth[dest], curr = dest; i-- > 0; curr = parent[curr]) pOutBuffer[i] = curr;
  }
  // return distance
  return depth[dest];
}

// int main() {
//   // nStartX,  nStartY,  nTargetX,  nTargetY, pMap,  nMapWidth,  nMapHeight,  pOutBuffer,  nOutBufferSize
//   int nStartX = 0, nStartY = 0;
//   int nTargetX = 2, nTargetY = 0;
//   int nMapWidth = 5, nMapHeight = 5;
//   const int nOutBufferSize = 100;

//   unsigned char pMap[] = {1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1};
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
//   if (length <= nOutBufferSize) {
//     for (int i = 0; i < length; i++) {
//       cout << pOutBuffer[i] << " ";
//     }
//   }
//   cout << "\n";

//   cout << length << "\n";
// }
