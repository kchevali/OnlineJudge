// Tree Algorithms

#include "set.cpp"

//================================================================================================================================================
// Minimum Spanning Tree

typedef tuple<o, l, l> T;
typedef vector<T> vT;
typedef vector<vT> vvT;
typedef pair<l, l> ll;
typedef vector<bool> vb;
typedef priority_queue<T, vector<T>, less<T>> pq;  // max out

vvT adj;
vector<ll> result;
// result = vector<ll>();mst();
l prim_mst() {
  double weight = 0;
  vb visited(adj.size(), false);
  pq q;

  visited[0] = true;
  for (auto x : adj[0]) q.push(x);

  while (!q.empty()) {
    auto t = q.top();
    q.pop();

    double w = get<0>(t);
    l a = get<1>(t), b = get<2>(t);

    if (!visited[b]) {
      weight += w;
      result.push_back((ll){a, b});  // store the MST
      visited[b] = true;
      for (auto x : adj[b]) {
        if (!visited[get<2>(x)]) q.push(x);
      }
    }
  }
  return weight;  // return MST
}

// example:

/*
        //      1     6
        //  0 ---- 3 ---- 4
        //  |    / |    / |
        // 3|   /  |1  /  |2
        //  |  /3  |  /5  |
        //  | /    | /    |
        //  1 ---- 2 ---- 5
        //     1       4

         * input:
         *
0 3 1
0 1 3
1 2 1
1 3 3
2 3 1
2 4 5
2 5 4
3 4 6
4 5 2

         */
// l vertex = 6;
// vector<ll> result;
// T edge(vertex, vector<tuple<double, l, l>>());

// l main() {
//   l index = 0;
//   for (l i = 0; i < 9; i++) {
//     l a, b;
//     double w;
//     cin >> a >> b >> w;
//     edge[a].push_back((tuple<double, l, l>){-w, a, b});
//     edge[b].push_back((tuple<double, l, l>){-w, b, a});
//   }
//   l w = mst(edge, result);
//   cout << w << endl;
//   for (auto p : result) {
//     cout << p.X << " " << p.Y << endl;
//   }
//   // weight = 9, result = {0-3, 3-2, 2-1, 2-5, 5-4}
// }

// Kruskal’s MST

// edges is the graph, n is the number of vertex
// return the MST

// #include "set.cpp"  //import union find disjol set
typedef double d;
typedef tuple<d, l, l> T;
typedef vector<T> vT;
typedef vector<vT> vvT;

d weight;
vT kruskal_mst(vT &v, l n) {
  sort(v.begin(), v.end());
  weight = 0;
  vT result = vT();
  for (T e : v) {
    if (!isSameSet(get<1>(e), get<2>(e))) {
      result.push_back(e);
      unionSet(get<1>(e), get<2>(e));
      weight += get<0>(e);
    }
  }
  return result;
}

//================================================================================================================================================
// Segment Tree (RMQ, RSQ)
// Solve problems that have a lot of range minimum/maximum/sum query.
// e.g. Give a list of number {4, 3, 5, 2, 3, 6, 1}, what is the maximum number
// from index 2 to 5. Following code include RMQ with lazy update, if the number
// list is static, then ignore the lazy update code.

// This code is for Range Minimum Query. Need a little change to apply for Range
// Maximum Query and Range Sum Query.

// VAR Notation: minQuery/maxQuery/sumQuery
// Ranged Minimum/Maximum/Sum Query problem   (RMQ/RSQ)

// #define MID(x, y) x + (y - x) / 2
// #define inf 0x3f3f3f3fLL
// class SegmentTree {
//  public:
//   SegmentTree(vl in) : input(in), tree(in.size() * 4, inf), lazy(tree.size(), 0) { construct(0, input.size() - 1, 0); }  // VAR: inf,-inf,0

//   // QUERY
//   l query(l low, l high) { return query(low, high, 0, input.size() - 1, 0); }
//   l queryRange(l qLow, l qHigh) { return queryRange(qLow, qHigh, 0, input.size() - 1, 0); }

//   // UPDATE
//   void updatePoint(l index, l delta) { updatePoint(index, delta, 0, input.size() - 1, 0); }
//   void updateRange(l sPos, l ePos, l delta) { updateRange(sPos, ePos, delta, 0, input.size() - 1, 0); }

//  private:
//   vl tree, input, lazy;  // lazy is for lazy propagation

//   void construct(l low, l high, l pos) {
//     if (low == high) {
//       tree[pos] = input[low];
//       return;
//     }
//     l m = MID(low, high);
//     construct(low, m, pos * 2 + 1);
//     construct(m + 1, high, pos * 2 + 2);

//     // VAR: min()/max()/+
//     tree[pos] = min(tree[pos * 2 + 1], tree[pos * 2 + 2]);
//   }

//   // qlow - query low, qhigh - query high, low-search low, high - search high
//   l query(l qlow, l qhigh, l low, l high, l pos) {
//     if (qlow > high || qhigh < low) return inf;  // VAR: inf,-inf,0
//     if (qlow <= low && qhigh >= high) return tree[pos];
//     l m = MID(low, high);

//     // VAR: min()/max()/+
//     return min(query(qlow, qhigh, low, m, pos * 2 + 1), query(qlow, qhigh, m + 1, high, pos * 2 + 2));
//   }

//   // This is for updating one value of the data
//   void updatePoint(l index, l delta, l low, l high, l pos) {
//     if (index == low && index == high) {
//       input[index] += delta;
//       tree[pos] = input[index];
//     }
//     if (index > high || index < low) return;
//     l m = MID(low, high);
//     updatePoint(index, delta, low, m, pos * 2 + 1);
//     updatePoint(index, delta, m + 1, high, pos * 2 + 2);

//     // VAR: min()/max()/+
//     tree[pos] = min(tree[pos * 2 + 1], tree[pos * 2 + 2]);
//   }

//   // previous code is standard rmq segment tree next is lazy updates (used when the problem requires dynamic updates)
//   // UPDATE: inc data from sPos to ePos by delta
//   void updateRange(l sPos, l ePos, l delta, l low, l high, l pos) {
//     if (low > high) return;
//     if (lazy[pos] != 0) {
//       tree[pos] += lazy[pos];  // += lazy[pos] * (high - low + 1); if is rsq//VAR
//       if (low != high) {
//         lazy[pos * 2 + 1] += lazy[pos];
//         lazy[pos * 2 + 2] += lazy[pos];
//       }
//       lazy[pos] = 0;
//     }

//     if (sPos > high || ePos < low) return;

//     if (sPos <= low && ePos >= high) {
//       tree[pos] += delta;  // += delta * (high - low + 1); if is rsq//VAR
//       if (low != high) {
//         lazy[pos * 2 + 1] += delta;
//         lazy[pos * 2 + 2] += delta;
//       }
//       return;
//     }

//     l m = MID(low, high);
//     updateRange(sPos, ePos, delta, low, m, pos * 2 + 1);
//     updateRange(sPos, ePos, delta, m + 1, high, pos * 2 + 2);
//     // VAR: min()/max()/+
//     tree[pos] = min(tree[pos * 2 + 1], tree[pos * 2 + 2]);
//   }

//   // QUERY: lazy version of RMQ
//   l queryRange(l qLow, l qHigh, l low, l high, l pos) {
//     if (low > high) return inf;  // VAR: inf,-inf,0
//     if (lazy[pos] != 0) {
//       tree[pos] += lazy[pos];  // += lazy[pos] * (high - low + 1); if is rsq//VAR
//       if (low != high) {
//         lazy[pos * 2 + 1] += lazy[pos];
//         lazy[pos * 2 + 2] += lazy[pos];
//       }
//       lazy[pos] = 0;
//     }

//     if (qLow > high || qHigh < low) return inf;  // VAR: inf,-inf,0
//     if (qLow <= low && qHigh >= high) return tree[pos];

//     l m = MID(low, high);

//     // VAR: min()/max()/+
//     return min(queryRange(qLow, qHigh, low, m, 2 * pos + 1), queryRange(qLow, qHigh, m + 1, high, 2 * pos + 2));
//   }
// };

// //========================================================================================
// // V3 - Persistent Segment Tree
// //========================================================================================

// // PROBLEMS: https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-12
// // #define inf 0x3f3f3f3fLL
// template <class D>
// class STNode {
//  public:
//   D value, lazy;
//   STNode<D> *left = NULL, *right = NULL, *pNode = NULL;  // pNode - persistence
//   l low, high;

//   STNode() {}
//   STNode(STNode<D> *pNode, l low, l high, D defaultValue) {
//     this->pNode = pNode;
//     this->low = low;
//     this->high = high;
//     if (pNode != NULL) {
//       this->value = pNode->value;
//       this->lazy = pNode->lazy;
//     } else {
//       this->value = defaultValue;
//       this->lazy = defaultValue;
//     }
//   }
//   void print() {
//     if (left != NULL) {
//       left->print();
//       right->print();
//     }
//     cout << "[" << low << ":" << high << "] = " << value << ", " << lazy << "\n";
//   }
// };

// template <class D>  // long long
// class ST {
//  public:
//   //"empty" value is maxValue()
//   ST(vector<D> &in) : input(in) { roots.push_back(construct(new STNode<D>(NULL, 0, input.size() - 1, maxValue()), 0, input.size() - 1)); }

//   D queryRange(l a, l b, l rootIndex = 0) { return _queryRange(roots[rootIndex], a, b); }
//   void updateRange(l a, l b, D delta) { updateRange(roots[0], a, b, delta); }
//   void persistUpdate(l a, l b, D delta, l rootIndex) {
//     auto root = new STNode<D>(roots[rootIndex], 0, input.size() - 1, maxValue());
//     roots.push_back(construct(root, a, b));
//     updateRange(root, a, b, delta);
//   }
//   void print(l rootIndex = 0) {
//     roots[rootIndex]->print();
//     cout << "\n";
//   }

//   //  private: //must hide for sub classes
//   STNode<D> *construct(STNode<D> *node, l a, l b) {
//     if (a > node->high || b < node->low) return node->pNode;

//     if (node->low == node->high) {
//       if (node->pNode == NULL) node->value = input[node->low];
//       return node;
//     }

//     l m = node->low + (node->high - node->low) / 2;
//     node->left = construct(new STNode<D>(node->pNode == NULL ? NULL : node->pNode->left, node->low, m, maxValue()), a, b);
//     node->right = construct(new STNode<D>(node->pNode == NULL ? NULL : node->pNode->right, m + 1, node->high, maxValue()), a, b);
//     if (isPassUp()) node->value = cmp(node->left->value, node->right->value);
//     return node;
//   }

//   void runLazy(STNode<D> *node) {
//     if (node->lazy != maxValue()) {
//       if (node->low != node->high) lazyChildren(node);
//       applyLazy(node);
//       node->lazy = maxValue();
//     }
//   }

//   D _queryRange(STNode<D> *node, l a, l b) {
//     if (node->low > node->high || a > node->high || b < node->low) return maxValue();
//     runLazy(node);
//     if ((a <= node->low && b >= node->high) || (!isPassUp() && node->value != maxValue())) return node->value;
//     return cmp(_queryRange(node->left, a, b), _queryRange(node->right, a, b));
//   }

//   void updateRange(STNode<D> *node, l a, l b, D delta) {
//     if (node->low > node->high || a > node->high || b < node->low) return;
//     // cout << "UPDATE: " << node->low << " " << node->high << "\n";
//     runLazy(node);
//     if (a <= node->low && b >= node->high) {
//       if (node->low != node->high) deltaChildren(node, delta);
//       applyDelta(node, delta);
//       return;
//     }
//     passDown(node);
//     updateRange(node->left, a, b, delta);
//     updateRange(node->right, a, b, delta);
//     if (isPassUp()) node->value = cmp(node->left->value, node->right->value);
//   }

//   virtual D maxValue() { return D(); }
//   virtual bool isPassUp() { return true; }
//   virtual D cmp(D a, D b) { return D(); }
//   virtual void applyLazy(STNode<D> *node) {}
//   virtual void lazyChildren(STNode<D> *node) {}
//   virtual void applyDelta(STNode<D> *node, D delta) {}
//   virtual void deltaChildren(STNode<D> *node, D delta) {}
//   virtual void passDown(STNode<D> *node) {}

//   vector<D> &input;
//   vector<STNode<D> *> roots;
// };

// template <class D>
// class MinMaxST : public ST<D> {
//  public:
//   MinMaxST(vector<D> in) : ST<D>(in) {}
//   virtual D maxValue() { return inf; }  //-inf
//   bool isPassUp() { return true; }
//   virtual D cmp(D a, D b) { return min(a, b); }  // max
//   virtual void applyLazy(STNode<D> *node) { node->value += node->lazy; }
//   void lazyChildren(STNode<D> *node) {
//     node->left->value += node->lazy;
//     node->right->value += node->lazy;
//   }
//   virtual void applyDelta(STNode<D> *node, D delta) { node->value += delta; }
//   void deltaChildren(STNode<D> *node, D delta) {
//     node->left->lazy += delta;
//     node->right->lazy += delta;
//   }
//   void passDown(STNode<D> *node) {}
// };

// template <class D>
// class SumST : MinMaxST<D> {
//  public:
//   SumST(vector<D> in) : MinMaxST<D>(in) {}
//   D maxValue() { return 0; }
//   D cmp(D a, D b) { return a + b; }
//   void applyLazy(STNode<D> *node) { node->value += node->lazy * (node->high - node->low + 1); }
//   void applyDelta(STNode<D> *node, D delta) { node->value += delta * (node->high - node->low + 1); }
// };

// template <class D>
// class SetST : public ST<D> {
//  public:
//   SetST(vector<D> in) : ST<D>(in) {}
//   D maxValue() { return inf; }
//   bool isPassUp() { return false; }
//   D cmp(D a, D b) { return a == maxValue() ? b : a; }
//   void applyLazy(STNode<D> *node) { node->value = node->lazy; }
//   void lazyChildren(STNode<D> *node) {
//     node->left->value = node->lazy;
//     node->right->value = node->lazy;
//   }
//   void applyDelta(STNode<D> *node, D delta) { node->value = delta; }
//   void deltaChildren(STNode<D> *node, D delta) {
//     if (node->value != maxValue()) {
//       node->left->lazy = delta;
//       node->right->lazy = delta;
//       node->value = maxValue();
//     }
//   }
//   void passDown(STNode<D> *node) {
//     if (node->value != maxValue()) {
//       node->left->lazy = node->value;
//       node->right->lazy = node->value;
//       node->value = maxValue();
//     }
//   }
// };

struct SetSegmentTree {
  static const l N = 100000;
  l num[N * 4], pos[N * 4], fill[N * 4];
  void push_down(l a, l b, l index) {
    if (!fill[index]) return;
    l mid = a + ((b - a) >> 1);
    num[index << 1] = num[index];
    pos[index << 1] = pos[index];

    num[index << 1 | 1] = num[index];
    pos[index << 1 | 1] = pos[index] + mid - a + 1;

    fill[index << 1] = fill[index << 1 | 1] = 1;
    fill[index] = 0;
  }
  void update(l a, l b, l index, l x, l ql, l qr) {
    if (a >= ql && b <= qr) {
      num[index] = x;
      pos[index] = a - ql + 1;
      fill[index] = 1;
      return;
    }
    l mid = a + ((b - a) >> 1);
    push_down(a, b, index);
    if (mid >= ql) update(a, mid, index << 1, x, ql, qr);
    if (mid < qr) update(mid + 1, b, index << 1 | 1, x, ql, qr);
  }
  l query(l a, l b, l index, l p) {
    if (a == b) return index;
    l mid = a + ((b - a) >> 1);
    push_down(a, b, index);
    if (mid >= p)
      return query(a, mid, index << 1, p);
    else
      return query(mid + 1, b, index << 1 | 1, p);
  }
};
class SegmentTree {  // Min, Max, Sum
 public:
  static const l N = 100000;
  l length, in[N], num[N * 4], lazy[N * 4];
  void build(l length) {
    this->length = length;
    build(1, length - 1, 1);
  }
  void update(l x, l ql, l qr) { update(1, length - 1, 1, x, ql, qr); }
  l query(l ql, l qr) { return query(1, length - 1, 1, ql, qr); }

 private:
  l build(l a, l b, l index) {
    lazy[index] = 0;
    if (a == b) return num[index] = in[a];  // set to 0 if starting with empty
    l mid = a + ((b - a) >> 1);
    l left = build(a, mid, index << 1), right = build(mid + 1, b, index << 1 | 1);
    return num[index] = min(left, right);
  }
  void push_down(l index) {
    if (!lazy[index]) return;
    num[index << 1] += lazy[index];
    num[index << 1 | 1] += lazy[index];
    lazy[index << 1] += lazy[index];
    lazy[index << 1 | 1] += lazy[index];
    lazy[index] = 0;
  }
  l update(l a, l b, l index, l x, l ql, l qr) {
    cout << "U: " << a << " " << b << "\n";
    if (a >= ql && b <= qr) {
      lazy[index] += x;
      return num[index] += x;
    }
    l mid = a + ((b - a) >> 1);
    push_down(index);
    l left = mid >= ql ? update(a, mid, index << 1, x, ql, qr) : num[index << 1];
    l right = mid < qr ? update(mid + 1, b, index << 1 | 1, x, ql, qr) : num[index << 1 | 1];

    cout << "U2: " << a << " " << b << " L:" << left << " R: " << right << "\n";
    return num[index] = min(left, right);
  }
  l query(l a, l b, l index, l ql, l qr) {
    // cout << "Q: " << a << " " << b << "\n";
    if (a >= ql && b <= qr) return num[index];
    l mid = a + ((b - a) >> 1);
    push_down(index);
    l left = mid >= ql ? query(a, mid, index << 1, ql, qr) : inf;
    l right = mid < qr ? query(mid + 1, b, index << 1 | 1, ql, qr) : inf;
    return min(left, right);
  }
};

int main() {
  vector<l> in = {5, 3, 1, 4, 6, 8, 9};
  SegmentTree tree;
  for (l i = 0; i < in.size(); i++) tree.in[i + 1] = in[i];
  tree.build(in.size());

  tree.update(5, 3, 5);
  for (l i = 1; i <= tree.length - 2; i++) {
    l q = tree.query(i, i + 2);
    cout << i << " " << (i + 2) << " = " << q << "\n";
  }
}
//================================================================================================================================================
