// Old Code that was really awesome but just wasn't good enough

#include "all.cpp"

// Finds the envelope of several polygons - concave/convex
// Also finds the holes that are not covered - not shown here - found in
// abstractart(kattis). Was used to find the overlapping area use java.geom.Area
// instead
void unionPolygonsHelper(voo &ans, vvoo &polys, l shape, l i0) {
  l N = polys.size(), n = polys[shape].size(), j, k, i1;
  oo prev = ans[ans.size() - 1];
  fpp(i1, 0, n) {  // pts of poly[shape]
    l i = (i1 + i0) % n;
    oo curr = polys[shape][i];
    l shape_i, pt_i;
    o dist, minDist = linf;
    oo pt, best_pt;

    fpp(j, 0, N) {  // all polys
      if (shape != j) {
        l m = polys[j].size();
        fpp(k, 0, m) {  // all pts of poly[j]
          oo a = polys[j][(k + m - 1) % m], b = polys[j][k];
          if (ptSegSegIntersect(prev, curr, a, b, pt) == 0 &&
              (dist = distSq(pt, prev)) < minDist && dist > 0) {
            shape_i = j;
            pt_i = k;
            minDist = dist;
            best_pt = pt;
          }
        }
      }
    }
    if (minDist == linf) {
      if (polys[shape][i] == firstPoint) return;
      ans.PB(polys[shape][i]);
      prev = curr;
    } else {
      ans.PB(best_pt);
      unionPolygonsHelper(ans, polys, shape_i, pt_i);
      return;
    }
  }
}

voo unionPolygons(vvoo &polys) {
  l shape = 0, i, j, k, n = polys.size(), m;
  fpp(i, 1, n) {
    rotateBottomToIndexZero(polys[i]);
    if (lexComp(polys[i][0], polys[shape][0])) shape = i;
  }
  voo ans = voo();
  ans.PB(firstPoint = polys[shape][0]);
  unionPolygonsHelper(ans, polys, shape, 1);
  return ans;
}