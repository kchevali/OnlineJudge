#include "../../Template.cpp"
vector<tuple<l, l, l, l>> v;

l search(l index) {
  if (G(v[index], 2) == 1) {
    return G(v[index],);
  }
  l i, time = L_INF, j;
  fpp(i, 0, index) {
    if (G(v[index], 2) == G(v[i], 3)) {
      time = min(time, search(j = i));
    }
  }
  return time + POW(G(v[index], 0) - G(v[j], 1));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n, m, i, j;
  I n >> m;

  fpp(i, 0, m) {
    l a, b, s, e;
    I a >> b >> s >> e;
    v.PB(MT(e, s, a, b));
  }
  sort(v.begin(), v.end());

  fpp(i, 0, m) {
    // l x = 1, t = 0;
    // fpp(j, 0, i) {}
    C search(i) E;
  }
}

/*
3 5
1 1 10 20 1 2 30 40 1 2 50 60 1 2 70 80 2 3 90 95

1900
*/
