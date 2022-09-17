#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef tuple<l,l,l> pokestop;
typedef tuple<l,l,l> edge;

constexpr l N = 15;
l dp[(1 << (N+5)) + 10];

//ubsand - check for undefined behavior
//assert everything

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // bool unusedVariable = 0;
  l n = 0;
  cin >> n;
  
  pokestop pokestops[n + 1];
  
  unordered_map<string, l> ids;
  
  memset(pokestops, 0, sizeof(pokestops[0]));
  l idCount = 0;
  
  for(l i = 1; i <= n; i++){
    auto &[x, y, id] = pokestops[i];
    string name;
    cin >> x >> y >> name;
    // assert(!cin.fail());

    if(ids.find(name) == ids.end()){
      id = 1 << (idCount++);
      ids[name] = id;
    } else {
      id = ids[name];
    }
  }
  memset(dp, 0x3f, sizeof(dp));

  stack<edge> edges;
  edges.push({(1<<idCount) - 1, 0, 0});

  l minDist = 2e9;
  while(!edges.empty()){
    auto [canGo, idx, total] = edges.top();
    edges.pop();
    auto [x, y, id] = pokestops[idx];
    l originDist = total + abs(x) + abs(y);
    if(originDist >= minDist) continue;

    if(canGo == 0) {
      minDist = originDist;
      // cout << "#" << minDist << " " << originDist << "\n";
      continue;
    }
    for(l i = 1; i <= n; i++){
      auto [stopX, stopY, stopId] = pokestops[i];
      if((stopId & canGo) == 0)continue;
      l nextCanGo = canGo & (~stopId);
      l dpId = (nextCanGo << 5) + i;
      l nextTotal = total + abs(x - stopX) + abs(y - stopY);
      if(nextTotal >= dp[dpId] || nextTotal >= minDist) continue;
      dp[dpId] = nextTotal;
      edges.push({nextCanGo, i, nextTotal});
    }
  }
  cout << minDist << "\n";
}

/*
20
-100 0 a
100 0 a
-100 1 b
100 1 b
-100 2 c
100 2 c
-100 3 d
100 3 d
-100 4 e
100 4 e
-100 5 f
100 5 g
-100 6 h
100 6 i
-100 7 j
100 7 k
-100 8 l
100 8 m
-100 9 n
100 9 o
Sol: 14

14
-4 2 a
-1 -5 a
4 -1 b
3 3 b
-3 -1 c
0 0 c
-4 2 d
-4 -4 d
0 -3 e
2 1 e
-4 -1 f
-3 -2 f
-3 -3 g
-4 1 g
Sol:22


*/