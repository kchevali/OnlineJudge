
#include <bits/stdc++.h>
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define gc getchar_unlocked
#define fpp(i, a, b) for (i = a; i < b; i++)
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

// THINGS TO DO: TRY MAX BIPARTITE MATCHING INSTEAD OF: place()

void read(l &x) {  // cannot be use with cin or something
  l c = gc();
  x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc())
    ;
  if (c == '-') {
    neg = 1;
    c = gc();
  }
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
  if (neg) x = -x;
}

vvl v = vvl(9, vl(9, 0));
void run();
bool isError();

bool canPlace(l i, l j, l num) {
  // C "Checking if col/row/square of" _ i _ j _ "contains" _ num E;
  if (v[i][j] > 0) {
    return false;
  }
  l x;
  fpp(x, 0, 9) {
    if (v[i][x] == num || v[x][j] == num ||
        v[(i / 3) * 3 + (x / 3)][(j / 3) * 3 + (x % 3)] == num) {
      return false;
    }
  }
  return true;
}

void print() {
  l i, j;
  string out = "";
  fpp(i, 0, 9) {
    fpp(j, 0, 9) { out += v[i][j] > 0 ? to_string(v[i][j]) : "."; }
    out += "\n";
  }
  C out;
}

bool isFull() {
  l i, j;
  fpp(i, 0, 9) {
    fpp(j, 0, 9) {
      if (v[i][j] <= 0) {
        return false;
      }
    }
  }
  return true;
}

bool place(l i, l j, l num) {
  C(isFull() ? "FULL" : "MORE SPACE") E;
  if (!canPlace(i, j, num) || isFull()) {
    return false;
  }

  l x, y;
  vvl copy = v;
  v = vvl(9, vl(9, 0));
  fpp(y, 0, 9) {
    fpp(x, 0, 9) { v[y][x] = copy[y][x]; }
  }
  v[i][j] = num;
  run();
  print();
  C "--" E;
  bool err = isError();
  v = copy;
  return !err;
}

bool checkError(l i, l j, l num, bool &match, l &count) {
  if (v[i][j] == num) {
    if (match) return true;
    match = true;
  } else if (!place(i, j, num)) {
    count++;
  }
  return false;
}

bool isError() {
  l i, j, num;
  fpp(num, 1, 10) {
    fpp(i, 0, 9) {
      l col = 0, row = 0, sq = 0;
      bool matchCol = false, matchRow = false, matchSq = false;
      fpp(j, 0, 9) {
        if (checkError(i, j, num, matchCol, col)) return true;
        if (checkError(j, i, num, matchRow, row)) return true;
        if (checkError(3 * (i / 3) + j / 3, 3 * (i % 3) + j % 3, num, matchSq,
                       sq))
          return true;
      }
      if (col == 9 || row == 9 || sq == 9) {
        return true;
      }
    }
  }
  return false;
}

// determines if a num has to be placed at this position
bool mustPlace(l i, l j, l num) {
  // C "Checking if must place" _ num _ " at " _ i _ j E;
  if (!canPlace(i, j, num)) {
    // C "This position has a" _ num _ "nearby" E;
    return false;
  }
  l x;
  l col = 0, row = 0, sq = 0;
  fpp(x, 0, 9) {
    if (x != j && canPlace(i, x, num)) {
      // C "NO COL - x =" _ x E;
      col++;
    }
    if (x != i && canPlace(x, j, num)) {
      // C "NO ROW - x =" _ x E;
      row++;
    }
    l i2 = (i / 3) * 3 + (x / 3),    // y
        j2 = (j / 3) * 3 + (x % 3);  // x
    if ((i2 != i || j2 != j) && canPlace(i2, j2, num)) {
      // C "NO SQ - x =" _ x E;
      sq++;
    }
  }
  return col == 0 || row == 0 || sq == 0;
}

void run() {
  l i, j, num;
  fpp(i, 0, 9) {
    fpp(j, 0, 9) {
      // C "Checking" _ i _ j _ v[i][j] E;
      if (v[i][j] <= 0) {
        fpp(num, 1, 10) {
          // C "Checking" _ i _ j _ num E;
          if (mustPlace(i, j, num)) {
            // C "Placing" _ i _ j _ num E;
            v[i][j] = num;
            run();
            return;
          }
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l i, j;
  fpp(i, 0, 9) {
    fpp(j, 0, 9) {
      char ch = gc();
      if (ch < '.') ch = gc();
      if (ch >= '0') v[i][j] = ch - '0';
    }
  }
  // if (mustPlace(0, 8, 9)) {
  //   C "Placing it!" E;
  //   v[0][8] = 9;
  // }
  run();
  if (isError()) {
    C "ERROR" E;
    return 0;
  }
  print();
}

/*

.........
...123...
......231
..1......
..2......
..3......
.........
.........
.........
//ERROR

*/
