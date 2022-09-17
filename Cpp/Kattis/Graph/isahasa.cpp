#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef pair<l,l> edge; // dest, isA

// BFS: Unweighted - find path from one source
constexpr l N = 500+10, inf = 0x3f3f3f3f3f3f3f3f;
l vis[N];
vector<edge> adj[N];
vector<string> names;
constexpr l ISA = 1, HASA = -1;
// Complexity O(V+E)
bool is_bfs(l src, l dest) {
  if(src == dest) return true; // can a class contain itself?

  queue<l> q;
  q.push(src);
  while (!q.empty()) {
    auto a = q.front();
    q.pop();
    for (auto [b, isB] : adj[a]) {
      if(vis[b] || isB == HASA) continue;
      if(b == dest) return true;
      vis[b] = true;
      q.push(b);
    }
  }
  return false;
}
bool has_bfs(l src, l dest) {
  queue<l> is_q, has_q;
  has_q.push(src);
  while (!is_q.empty() || !has_q.empty()) {
    l a;
    if(has_q.empty()) a = is_q.front(), is_q.pop();
    else a = has_q.front(), has_q.pop();

    for (auto [b, isB] : adj[a]) {
      // cout << "A: " << names[a] << " " << vis[a] << " B: " << names[b] << " IS: " << isB << " VIS: " << vis[b] << "\n";
      if(vis[b] == HASA) continue;
      if(vis[b] == ISA) {
          if(vis[a] == HASA || isB == HASA) {
              if(b == dest) return true;
              vis[b] = HASA;
              has_q.push(b);
          }
      }
      else {
          if(vis[a] == HASA || isB == HASA) {
              if(b == dest) return true;
              vis[b] = HASA;
              has_q.push(b);
          }
          else {
              vis[b] = ISA;
              is_q.push(b);
          }
      }
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n = 0, s, q;
  cin >> s >> q;

  unordered_map<string, l> ids;

  for(l i = 0; i < s; i++){
    string strA, strB, t;
    cin >> strA >> t >> strB;
    if(ids.find(strA) == ids.end()) ids[strA] = n++, names.push_back(strA);
    if(ids.find(strB) == ids.end()) ids[strB] = n++, names.push_back(strB);

    l a = ids[strA], b = ids[strB];
    adj[a].push_back({b, t == "is-a" ? ISA : HASA});
  }

  for(l i = 0; i < q; i++){
    string strA, strB, t;
    cin >> strA >> t >> strB;
    if(ids.find(strA) == ids.end()) ids[strA] = n++, names.push_back(strA);
    if(ids.find(strB) == ids.end()) ids[strB] = n++, names.push_back(strB);

    l a = ids[strA], b = ids[strB];
    memset(vis, 0, sizeof(vis[0]) * n);
    bool res = t == "is-a" ? is_bfs(a, b) : has_bfs(a, b);
    cout << "Query " << (i+1) << ": " << (res ? "true" : "false") << "\n";
  }
}
