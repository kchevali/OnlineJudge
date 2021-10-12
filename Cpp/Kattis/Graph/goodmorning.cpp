#include <bits/stdc++.h>
using namespace std;
typedef long long l;

// BFS: Unweighted - find path from one source
const l N = 15, inf = 0x3f3f3f3f3f3f3f3f;
vector<l> adj[N];
unordered_set<l> out;
// Complexity O(V+E)
void bfs(l src) {
  queue<pair<l,l>> q;
  q.push({src, 0});
  out.insert(0);
  while (!q.empty()) {
    auto [a, total] = q.front();
    q.pop();

    for (l b : adj[a]) {
      q.push({b,total});
    }

    total = 10 * total + a;
    if(total <= 200 && out.find(total) == out.end()){
      out.insert(total);
      q.push({a,total});
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l m, x;
  cin >> m;
  adj[1].push_back(2);
  adj[1].push_back(4);
  adj[2].push_back(3);
  adj[2].push_back(5);
  adj[3].push_back(6);
  adj[4].push_back(7);
  adj[4].push_back(5);
  adj[5].push_back(6);
  adj[5].push_back(8);
  adj[6].push_back(9);
  adj[7].push_back(8);
  adj[8].push_back(0);
  adj[8].push_back(9);
  bfs(1);

  for(l k = 0; k < m; k++){
    cin >> x;
    l best = 1000;
    for(l i = -1; i < 2; i+= 2){
      l j = 0;
      while(x + j >= 0 && x + j <= 200 && out.find(x + j) == out.end()) j += i;
      if(abs(j) < abs(best)) best = j;
    }
    cout << (x + best) << "\n";
  }

}
