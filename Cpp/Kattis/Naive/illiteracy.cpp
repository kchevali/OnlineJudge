#include <bits/stdc++.h>
using namespace std;
typedef long long l;


inline void getBits(l bits, l idx, l& ans){
  ans = ((bits >> (idx * 3)) & 0b111);
}

inline void setBits(l& bits, l value, l idx){
  bits = ((bits & (~(0b111 << (3*idx)))) | (value << (idx *  3)));
}

l match(l a, l b){
  l total = 0;
  for(l i = 0; i < 8; i++){
    l x, y;
    getBits(a, i, x);
    getBits(b, i, y);
    total += (x == y);
  }
  return -total;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l inf = 1e9, target = 0;
  unordered_set<l> dp;

  string start_, end_;
  cin >> start_ >> end_;
  l start = 0;
  for(l i = 0; i < 8; i++){
    setBits(start, start_[i] - 'A', i);
    setBits(target, end_[i] - 'A', i);
  }

  priority_queue<tuple<l, l, l>, vector<tuple<l,l,l>>, greater<tuple<l,l,l>>> q;
  q.push({0, match(start, target), start});

  if(start == target){
    cout << "0\n";
    return 0;
  }

  while(!q.empty()){
    auto [depth, _, a] = q.top();
    q.pop();

    for(l i = 0; i < 8; i++){
      l x, c = a, y;
      getBits(a, i, x);
      if(x == 0){
        if(i > 0){
          getBits(c, i - 1, y);
          setBits(c,(y + 1) % 6, i - 1);
        }
        if(i < 7){
          getBits(c, i + 1, y);
          setBits(c,(y + 1) % 6, i + 1);
        }
      }else if(x == 1){
        if(i > 0 && i < 7){
          getBits(c, i - 1, y);
          setBits(c, y, i + 1);
        }
      }else if(x == 2){
        getBits(c, 7 - i, y);
        setBits(c, (y + 1) % 6, 7 - i);
      }else if(x == 3){
        l dir = (i < 7 - i) ? -1 : 1;
        for(l j = i + dir; j >= 0 && j <= 7; j += dir){
          getBits(c, j, y);
          setBits(c, (y + 1) % 6, j);
        }
      }else if(x == 4){
        l dist = min(i, 7 - i);
        if(dist > 0){
          getBits(c, i + dist, y);
          setBits(c, (y + 1) % 6, i + dist);
          getBits(c, i - dist, y);
          setBits(c, (y + 1) % 6, i - dist);
        }
      }else{
        l idx = ((i & 1) == 0 ? (i + 10) / 2 : ((i + 1) / 2)) - 1;
        getBits(c, idx, y);
        setBits(c, (y + 1) % 6, idx);
      }
      if(a != c && dp.find(c) == dp.end()){
        if(c == target){
          cout << (depth + 1) << "\n";
          return 0;
        }
        dp.insert(c);
        q.push({depth+1, match(c, target), c});
      }
    }
  }
}
