#include <bits/stdc++.h>
using l = long long;

#define gc getchar_unlocked
void readInt(l &x) {
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

struct Node{
    l min, max, depth;
    Node(l min, l max, l depth): min(min), max(max), depth(depth) {}
};

int main() {
    l n;
    readInt(n);

    std::map<l, Node*> bst;
    bst.insert({n, new Node(1, n, 0)});

    l c = 0;
    for(l i = 0; i < n; i++){
        l x;
        readInt(x);
        
        auto it = bst.lower_bound(x);
        auto [key, parent_node] = (*it);
        bst.erase(key);
        if(parent_node->min <= x - 1){
            bst.insert({x-1, new Node(parent_node->min, x - 1, parent_node->depth + 1)});
        }
        if(x + 1 <= parent_node->max){
            bst.insert({parent_node->max, new Node(x + 1, parent_node->max, parent_node->depth + 1)});
        }
        c += parent_node->depth;
        printf("%lld\n", c);
    }
}
