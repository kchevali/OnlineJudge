// hilbert sort
#include <bits/stdc++.h>
using namespace std;
typedef long long l;

typedef tuple<l, l, l> pt;
typedef vector<pt> vpt;
typedef vector<string> vs;
#define PB emplace_back
#define X(x) get<0>(x)
#define Y(x) get<1>(x)
#define S(x) get<2>(x)
typedef vector<pair<l, l>> vll;

l N, S;

void hsort(vpt &pts) {
  l n = pts.size();
  if (n <= 1) return;
  // db(n);
  // for(auto p: pts)cout << "(" << X(p) << "," << Y(p) << ") ";
  // cout << "\n";
  vpt p1, p2, p3, p4;
  for (l i = 0; i < n; i++) {
    l x = X(pts[i]), y = Y(pts[i]), id = S(pts[i]);
    if (x < 0) {
      if (y < 0)
        p1.PB((pt){2 * y + S, 2 * x + S, id});
      else
        p2.PB((pt){2 * x + S, 2 * y - S, id});
    } else {
      if (y < 0)
        p4.PB((pt){-2 * y - S, -2 * x + S, id});
      else
        p3.PB((pt){2 * x - S, 2 * y - S, id});
    }
  }
  hsort(p1);
  hsort(p2);
  hsort(p3);
  hsort(p4);
  l i = 0;
  for (pt &x : p1) pts[i++] = x;
  for (pt &x : p2) pts[i++] = x;
  for (pt &x : p3) pts[i++] = x;
  for (pt &x : p4) pts[i++] = x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> N >> S;
  vpt pts(N);
  vll names(N);
  for (int i = 0; i < N; i++) {
    auto &p = pts[i];
    cin >> X(p) >> Y(p);
    names[i].first = X(p);
    names[i].second = Y(p);
    X(p) = 2 * X(p) - S;
    Y(p) = 2 * Y(p) - S;
    S(p) = i;
  }
  hsort(pts);
  for (auto &p : pts)
    cout << names[S(p)].first << " " << names[S(p)].second << "\n";
}
/*

 14 25
 5 5 Honolulu
 5 10 PugetSound
 5 20 Victoria
 10 5 Berkeley
 10 10 Portland
 10 15 Seattle
 10 20 Vancouver
 15 5 LasVegas
 15 10 Sacramento
 15 15 Kelowna
 15 20 PrinceGeorge
 20 5 Phoenix
 20 10 SaltLakeCity
 20 20 Calgary


*/