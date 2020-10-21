#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;


vl p, ranks, setSize;
l numSets;  // the number of disjoint sets
l findSet(l i) { return p[i] == i ? i : p[i] = findSet(p[i]); }
// return true if element i and j are in the same set, return false otherwise
bool isSameSet(l i, l j) { return findSet(i) == findSet(j); }
// union two sets that contain element i and j
void unionSet(l i, l j) {
  l x = findSet(i), y = findSet(j);
  if (x == y) return;
  // ranks is used to keep the tree short
  if (ranks[x] > ranks[y]){
    p[y] = x;
    setSize[x] += setSize[y];
  }else {
    p[x] = y;
    setSize[y] += setSize[x];
    if (ranks[x] == ranks[y]) ranks[y]++;
  }
}
l sizeOfSet(l i) { return setSize[findSet(i)]; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l t;
  cin >> t;
  cin.ignore();
  for (l i = 0; i < t; i++) {
    p = vl(26);
    ranks = vl(26, 0);
    setSize = vl(26, 1);
    iota(p.begin(), p.end(), 0);
    l in = 0,x,y;
    string line;
    while(true){
      cin >> line;
      if(line[0] == '*')break;
      unionSet( line[1]-'A',line[3]-'A');
      // cout << "Join: " << (line[1]-'A') << " " << (line[3]-'A') << "\n";
    }
    vl valid(26,0);
    cin >> line;
    for(l i = 0; i < line.length(); i+=2){
      valid[line[i] - 'A'] = 1;
    }
    
    l forest = 0, acorn = 0;
    for (int i = 0; i < 26; i++) {

      if(valid[i] == 0)continue;

      l root = findSet(i);
      // cout << i << ": " << p[i] << "\n";
      if(root == i){
        acorn += sizeOfSet(root) == 1;
        forest += sizeOfSet(root) > 1;
      }
    }
    printf("There are %lld tree(s) and %lld acorn(s).\n", forest, acorn);
  }
}
/*
1
(B,C)
*****
A,B,C

1
(A,Z)
(D,F)
(Q,F)
(Y,N)
(T,Q)
(B,T)
**
A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z

*/