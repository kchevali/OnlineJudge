#include "../../Template.cpp"
// TLE - need to optimize

l fac(l x) { return x < 3 ? x : x * fac(x - 1); }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n, x, i;
  I n >> x;
  vl p(n), v(n);
  fpp(i, 0, n) I p[i];
  iota(v.begin(), v.end(), 0);

  l p0 = *max_element(p.begin(), p.end()), tot = 0;
  do {
    l mask = 0, sum = 0, cul = 0, p1 = p0;
    bool good = true;
    fpp(i, 0, n) {
      l j = v[i];
      mask |= 1 << j;
      p1 = max(p1 + 1, p[j] + sum);
      l inc = p1 - p[j];
      sum = inc;
      sum = p1 - p[j];
      DB(p1, sum);
      // if (sum += (n - i) * (p1 = (p1 + 1 - p[j])) > x) {
      //   good = false;
      //   break;
      // }
    }
    if (!good) continue;

    // l sum = 0, p1 = p0, inc = 0;
    // fpp(i, 0, n) {
    //   if (p1 == p[i]) {
    //     C tot E;
    //     return 0;
    //   }
    //   inc = max(inc + (i > 0 && p[i] < p[i - 1]), p1 - p[i] + 1);
    //   sum += inc;
    //   if (sum > x) break;
    //   p1 = p[i] + inc;
    // }
    // tot += (sum <= x);
    ARR(v);
  } while (next_permutation(v.begin(), v.end()));
  C tot E;
  return 0;
}