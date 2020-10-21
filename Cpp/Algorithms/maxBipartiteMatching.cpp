#include "../Template.cpp"

l aug(l left, vvl &adj, vl &match, vb &vis) {
  if (vis[left]) return 0;
  vis[left] = true;

  for (auto right : adj[left]) {
    if (match[right] == -1 || aug(match[right], adj, match, vis) == 1) {
      match[right] = left;
      return 1;
    }
  }

  return 0;
}

l getMatching(l v, l v_l, vvl adj) {
  l count = 0;
  vl match(v, -1);
  for (l i = v_l; i-- > 0;) {
    vb vis(v_l, false);
    count += aug(i, adj, match, vis);
  }
  return count;
}

int main() {
  l v = 8, v_l = 4;  //  V: total vertex, V_l: vertex on left side
  vvl adj(v, vl());
  // just ignore vertex 0
  // adj[1].PB(3); // 1 -- 3
  // adj[1].PB(4); //   -
  // adj[2].PB(3); //    -
  //               //  2 -- 4

  adj[0].PB(4);
  adj[1].PB(5);
  adj[2].PB(7);
  adj[3].PB(6);
  adj[4].PB(1);
  adj[5].PB(1);
  adj[6].PB(1);

  cout << getMatching(v, v_l, adj) << endl;
  return 0;
}