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
const auto processor_count = std::thread::hardware_concurrency();

const int N = 1e7, inf = 0x3f3f3f3f;
int depth[N], rDepth[N], child[N], parent[N], grainSize = 128;
node* adj[N][4];
char vis[N], rVis[N], adjSize[N], runCount = 0;

// root of pennant has left or no children, else left & right
struct node {
  node *left, *right;
  int value;

  node(int value) : value(value), left(nullptr), right(nullptr) {}

  node* join(node* that) {  // this(root), that(root) -> this(root), that(only child of this)
    if (that != nullptr) that->right = this->left, this->left = that;
    return this;
  }

  node* split() {
    node* that = this->left;
    this->left = that->right, that->right = nullptr;
    return that;
  }
};

struct bag {
  // capacity = 2^r;
  node** s;
  int r, largest_nonempty_index;
  bag(int r) : largest_nonempty_index(-1) { this->s = new node*[this->r = r](); }

  ~bag() {
    this->clear();
    delete[] this->s;
  }

  void clear() {
    for (int i = 0; i <= largest_nonempty_index; i++) {
      delete s[i];
      s[i] = nullptr;
    }
    largest_nonempty_index = -1;
  }

  void insert(int value) { insert(new node(value)); }

  void insert(node* x) {
    int k = 0;
    while (s[k] != nullptr) x->join(s[k]), s[k++] = nullptr;
    s[k] = x;
    if (k > largest_nonempty_index) largest_nonempty_index = k;
  }

  void fullAdder(node* x, node* y, node* z, node* sum, node* carry) {
    int count = (x != nullptr) + (y != nullptr) + (z != nullptr);
    if (count != 2)
      carry = count == 3 ? y->join(z) : nullptr, sum = (x != nullptr ? x : (y != nullptr ? y : z));
    else  // count == 2
      sum = nullptr, carry = (x == nullptr ? y->join(z) : (y == nullptr ? x->join(z) : x->join(y)));
  }

  void join(bag* that) {
    node* c = nullptr;
    int max_nonempty_index = max(that->largest_nonempty_index, this->largest_nonempty_index);

    for (int k = 0; k <= max_nonempty_index; k++) fullAdder(this->s[k], that->s[k], c, this->s[k], c);
    if (c != nullptr) this->s[++max_nonempty_index] = c;
    this->largest_nonempty_index = max_nonempty_index;
    // size *= 2;
  }

  bag* split() {
    bag* that = new bag(r);
    node* x = s[0];
    s[0] = nullptr;

    for (int i = 1; i <= largest_nonempty_index; i++) {
      if (s[i] != nullptr) {
        that->s[i - 1] = s[i]->split();
        s[i - 1] = s[i], s[i] = nullptr;
      }
    }

    if (largest_nonempty_index != 0) that->largest_nonempty_index = --largest_nonempty_index;
    if (x != nullptr) insert(x);
    return that;
  }

  int size() {
    int sum = 0;
    for (int i = 0, bit = 1; i <= largest_nonempty_index; i++, bit <<= 1) {
      if (s[i] != nullptr) sum += bit;
    }
    return sum;
  }

  bool empty() { return largest_nonempty_index < 0; }
};

void processNode(node* x, bag* outBag, int d) {
  if (x->size() < grainSize) {
    queue<node*> q;
    q.push(x);
    while (!q.empty()) {
      node* a = q.front();
      q.pop();

      // parallel
      for (node* b : adj[a->value]) {
        if (depth[b->value] == inf) {
          depth[b->value] = d + 1;
          outBag->insert(b);
        }
      }

      if (a->left != nullptr) q.push(a->left);
      if (a->right != nullptr) q.push(a->right);
    }
    return;
  }
  node* newTree = x->split();

  // spawn
  processNode(newTree, outBag, d);
  processNode(x, outBag, d);
  // sync
}

void processLayer(bag* inBag, bag* outBag, int d) {
  // parallel
  for (int k = 0; k < floor(log2(inBag->size)); k++) {
    if (inBag->s[k] != nullptr) processNode(inBag->s[k], outBag, d);
  }
}

void PBFS(node* src, int n) {
  // parallel
  memset(depth, 0x3f, sizeof(int) * n);
  depth[src->value] = 0;
  int d = 0;
  bag v(n);
  v.insert(src);
  while (!v.empty()) {
  }
}

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

int main() {
  // nStartX,  nStartY,  nTargetX,  nTargetY, pMap,  nMapWidth,  nMapHeight,  pOutBuffer,  nOutBufferSize
  int nStartX = 0, nStartY = 0;
  int nTargetX = 3, nTargetY = 3;
  int nMapWidth = 4, nMapHeight = 4;
  const int nOutBufferSize = 12;

  unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int pOutBuffer[nOutBufferSize];
  int length = FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
  // FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
  // FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
  // FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);

  for (int i = 0, index = 0; i < nMapHeight; i++) {
    for (int j = 0; j < nMapWidth; j++, index++) {
      cout << (char)(pMap[index] + '0');
    }
    cout << "\n";
  }

  for (int i = 0; i < length; i++) {
    cout << pOutBuffer[i] << " ";
  }
  cout << "\n";

  cout << length << "\n";
}