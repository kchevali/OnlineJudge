#include "../all.cpp"

// getline(cin, str); - used w/ cin.ignore();

void readd(double &x) { scanf("%lf", &x); }

// typedef pair<l, l> ll;
// typedef v(ll) vll;
vll readPts(l n) {
  vll pts(n);
  for (auto &p : pts) {
    read(p.xx);
    read(p.yy);
  }
  return pts;
}

l i, j, h, w;
vvl m;
void getMatrix() {
  read(h);  //>>w;
  w = h;
  m = vvl(h, vl(w, 0));
  for (l i = 0; i < h; i++)
    for (l j = 0; j < w; j++) read(m[i][j]);
}

//-----------------------------------------------
// Creates adj list from a hxw matrix. Stores the i,j indices and the value
// inputted
typedef l d;  // weight type
typedef tuple<d, l, l> T;
typedef vector<vector<T>> vT;
// l i, j, h, w;
d x;
vT adj;
void matrixToAdjTuple() {
  read(h);  //>>w;
  w = h;
  adj = vT(h, vector<T>());
  fpp(i, 0, h) {
    fpp(j, 0, w) {
      read(x);
      adj[i].PB(make_tuple(x, i, j));
    }
  }
}
//-----------------------------------------------
// Creates fully connected adj list from h coords. Stores the i,j indices and
// the distance between
typedef double d;
typedef vector<pair<d, d>> vdd;
typedef tuple<d, l, l> T;
typedef vector<T> vT;
typedef vector<vT> vvT;
// l i, j, h;
d x;
vvT adjDis;
void coordToDistanceAdj() {
  read(h);
  vdd coords = vdd();
  d a, b;
  fpp(i, 0, h) {
    readd(a);
    readd(b);
    coords.PB(make_pair(a, b));
  }
  adjDis = vvT(h, vT());
  fpp(i, 0, h) {
    fpp(j, 0, h) {
      if (i < j) {
        d da = coords[i].first - coords[j].first, db = coords[i].second - coords[j].second, dis;
        dis = sqrt(da * da + db * db);
        adjDis[i].PB(make_tuple(dis, i, j));
        adjDis[j].PB(make_tuple(dis, j, i));
      }
    }
  }
}
//-----------------------------------------------
