#include "../Template.cpp"

const l N = 1e3;
vl adj[N];
l match[N];
bool vis[N];

l aug(l left) {
  vis[left] = true;
  for (auto& right : adj[left]) {
    if (match[right] == -1 || (!vis[match[right]] && aug(match[right]) == 1)) {
      match[right] = left;
      return 1;
    }
  }
  return 0;
}

l getMatching(l n, l n_left) {
  l count = 0;
  memset(match, -1, sizeof(l) * n);
  for (l i = n_left; i-- > 0;) {
    memset(vis, 0, sizeof(bool) * n_left);
    count += aug(i);
  }
  return count;
}

int main() {
  l n, n_left, edges;  //  V: total vertex, V_l: vertex on left side
  cin >> n >> n_left >> edges;
  for (l i = 0; i < edges; i++) {
    l a, b;
    cin >> a >> b;
    adj[a].push_back(b);  // ignore index 0?? - check this
  }

  cout << getMatching(n, n_left) << endl;
  return 0;
}

/*
12 6 8
0 7
0 8
2 6
2 9
3 8
4 8
4 9
5 11
Solution: 5

*/