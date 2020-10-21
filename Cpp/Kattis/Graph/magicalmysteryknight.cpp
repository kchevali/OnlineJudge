
#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<l> vl;
#define bit(x, b) bitset<b>(x).to_string()  // prints x with b bits

// GRID DILUTION - ROW/COL/SQR

// cond (a,b) -> (c,d) iff (a-c)**2 + (b-d)**2 == 5
// every 2x2 == 130
// first/last 4 rows/cols == 130

// 1x4 rows://PERFECT
// j / 4 + i * 2                  // x / 4 + y * 2
// inner index:j&3                //x&3
// full index:                    //a * 4 + b

// 4x1 cols:
// j * 2 + (i / 4)                // x * 2 + (y / 4)
// inner index:i&3                //y&3
// full index:                    // a / 2 + b * 8 + (a & 1) * 32

// 2x2 sqrs:
// j / 2 + (i / 2) * 4            // x / 2 + (y / 2) * 4
// inner index: ((i & 1) + j * 2) & 3   // ((y & 1) + x * 2) & 3
// full index:                    //a * 2 + (a / 4) * 8 + b / 2 + (b & 1) * 8

// https://open.kattis.com/contests/c7upgj/problems/magicalmysteryknight

l vis = 0;
l nums[8][8], org[8][8], getX[64], getY[64], sumArr[3][16], nArr[3][16], iArr[3][16];
l dirX[8]{1, 1, 2, 2, -1, -1, -2, -2};
l dirY[8]{2, -2, 1, -1, 2, -2, 1, -1};

stack<tuple<l, l, l, bool>> stk;

// group#0-15
l indexArr[3][8][8]{{{0, 0, 0, 0, 1, 1, 1, 1}, {2, 2, 2, 2, 3, 3, 3, 3}, {4, 4, 4, 4, 5, 5, 5, 5}, {6, 6, 6, 6, 7, 7, 7, 7}, {8, 8, 8, 8, 9, 9, 9, 9}, {10, 10, 10, 10, 11, 11, 11, 11}, {12, 12, 12, 12, 13, 13, 13, 13}, {14, 14, 14, 14, 15, 15, 15, 15}}, {{0, 2, 4, 6, 8, 10, 12, 14}, {0, 2, 4, 6, 8, 10, 12, 14}, {0, 2, 4, 6, 8, 10, 12, 14}, {0, 2, 4, 6, 8, 10, 12, 14}, {1, 3, 5, 7, 9, 11, 13, 15}, {1, 3, 5, 7, 9, 11, 13, 15}, {1, 3, 5, 7, 9, 11, 13, 15}, {1, 3, 5, 7, 9, 11, 13, 15}}, {{0, 0, 1, 1, 2, 2, 3, 3}, {0, 0, 1, 1, 2, 2, 3, 3}, {4, 4, 5, 5, 6, 6, 7, 7}, {4, 4, 5, 5, 6, 6, 7, 7}, {8, 8, 9, 9, 10, 10, 11, 11}, {8, 8, 9, 9, 10, 10, 11, 11}, {12, 12, 13, 13, 14, 14, 15, 15}, {12, 12, 13, 13, 14, 14, 15, 15}}};

// inner index#0-3
l innerArr[3][8][8]{{{0, 1, 2, 3, 0, 1, 2, 3}, {0, 1, 2, 3, 0, 1, 2, 3}, {0, 1, 2, 3, 0, 1, 2, 3}, {0, 1, 2, 3, 0, 1, 2, 3}, {0, 1, 2, 3, 0, 1, 2, 3}, {0, 1, 2, 3, 0, 1, 2, 3}, {0, 1, 2, 3, 0, 1, 2, 3}, {0, 1, 2, 3, 0, 1, 2, 3}}, {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {2, 2, 2, 2, 2, 2, 2, 2}, {3, 3, 3, 3, 3, 3, 3, 3}, {0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1}, {2, 2, 2, 2, 2, 2, 2, 2}, {3, 3, 3, 3, 3, 3, 3, 3}}, {{0, 1, 0, 1, 0, 1, 0, 1}, {2, 3, 2, 3, 2, 3, 2, 3}, {0, 1, 0, 1, 0, 1, 0, 1}, {2, 3, 2, 3, 2, 3, 2, 3}, {0, 1, 0, 1, 0, 1, 0, 1}, {2, 3, 2, 3, 2, 3, 2, 3}, {0, 1, 0, 1, 0, 1, 0, 1}, {2, 3, 2, 3, 2, 3, 2, 3}}};
l xArr[3][16][4]{{{0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}}, {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {1, 1, 1, 1}, {2, 2, 2, 2}, {2, 2, 2, 2}, {3, 3, 3, 3}, {3, 3, 3, 3}, {4, 4, 4, 4}, {4, 4, 4, 4}, {5, 5, 5, 5}, {5, 5, 5, 5}, {6, 6, 6, 6}, {6, 6, 6, 6}, {7, 7, 7, 7}, {7, 7, 7, 7}}, {{0, 1, 0, 1}, {2, 3, 2, 3}, {4, 5, 4, 5}, {6, 7, 6, 7}, {0, 1, 0, 1}, {2, 3, 2, 3}, {4, 5, 4, 5}, {6, 7, 6, 7}, {0, 1, 0, 1}, {2, 3, 2, 3}, {4, 5, 4, 5}, {6, 7, 6, 7}, {0, 1, 0, 1}, {2, 3, 2, 3}, {4, 5, 4, 5}, {6, 7, 6, 7}}};
l yArr[3][16][4]{{{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {1, 1, 1, 1}, {2, 2, 2, 2}, {2, 2, 2, 2}, {3, 3, 3, 3}, {3, 3, 3, 3}, {4, 4, 4, 4}, {4, 4, 4, 4}, {5, 5, 5, 5}, {5, 5, 5, 5}, {6, 6, 6, 6}, {6, 6, 6, 6}, {7, 7, 7, 7}, {7, 7, 7, 7}}, {{0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 2, 3}, {4, 5, 6, 7}}, {{0, 0, 1, 1}, {0, 0, 1, 1}, {0, 0, 1, 1}, {0, 0, 1, 1}, {2, 2, 3, 3}, {2, 2, 3, 3}, {2, 2, 3, 3}, {2, 2, 3, 3}, {4, 4, 5, 5}, {4, 4, 5, 5}, {4, 4, 5, 5}, {4, 4, 5, 5}, {6, 6, 7, 7}, {6, 6, 7, 7}, {6, 6, 7, 7}, {6, 6, 7, 7}}};
l odd[8][8]{{1, 0, 1, 0, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1, 0, 1}};

void print() {
  for (l i = 0; i < 8; i++) {
    for (l j = 0; j < 8; j++) {
      cout << nums[i][j] << " ";
    }
    cout << "\n";
  }
}

void verify() {
  for (l i = 0; i < 8; i++) {
    l rowTot = 0, colTot = 0;
    for (l j = 0; j < 8; j++) {
      colTot += nums[i][j];
      rowTot += nums[j][i];
    }
    if (colTot != 260 || rowTot != 260) {
      cout << "COL TOT: " << colTot << " ROW TOT: " << rowTot << "\n";
      assert(false);
    }
  }

  for (l n = 2; n <= 64; n++) {
    for (l i = 0; i < 8; i++) {
      for (l j = 0; j < 8; j++) {
        if (nums[i][j] == n - 1) {
          bool found = false;
          for (l k = 0; k < 8; k++) {
            for (l m = 0; m < 8; m++) {
              if (nums[k][m] == n) {
                found = true;
                if ((i - k) * (i - k) + (j - m) * (j - m) != 5) {
                  cout << "FAILED: " << (n - 1) << " " << n << "\n";
                  exit(1);
                }
              }
            }
          }
          if (!found) {
            cout << "MISSING: " << n << "\n";
            exit(1);
          }
        }
      }
    }
  }
  cout << "VERIFED\n";
}

bool setNum(l x, l y, l num) {  // num = 1-64
  for (l i = 0; i < 3; i++) {
    l index = indexArr[i][y][x];
    sumArr[i][index] += num;
    iArr[i][index] -= innerArr[i][y][x];
    nArr[i][index]++;
  }
  nums[y][x] = num;
  getX[num - 1] = x;
  getY[num - 1] = y;
  vis |= (1LL << (num - 1));
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  memset(sumArr, 0, sizeof(l) * 3 * 16);
  memset(nArr, 0, sizeof(l) * 3 * 16);
  memset(org, 0, sizeof(l) * 64);
  memset(getX, -1, sizeof(l) * 64);
  memset(getY, -1, sizeof(l) * 64);

  for (l i = 0; i < 3; i++)
    for (l j = 0; j < 16; j++) iArr[i][j] = 6;

  l startX, startY;
  for (l i = 0; i < 8; i++) {
    for (l j = 0; j < 8; j++) {
      scanf("%lld", &nums[i][j]);
      if (nums[i][j] != -1) {
        setNum(j, i, nums[i][j]);
        org[i][j] = 1;
        if (nums[i][j] == 1) {
          startY = i;
          startX = j;
        }
      };
    }
  }

  stk.push(make_tuple(startX, startY, 1, false));
  while (!stk.empty()) {
    l x, y, num, deleteNode;
    tie(x, y, num, deleteNode) = stk.top();

    if (deleteNode) {
      l dx, dy, dnum, deleteNode;
      tie(dx, dy, dnum, deleteNode) = stk.top();
      while (!stk.empty() && deleteNode) {
        stk.pop();
        l num = nums[dy][dx];
        if (num != -1) {
          for (l i = 0; i < 3; i++) {
            l index = indexArr[i][dy][dx];
            sumArr[i][index] -= num;
            nArr[i][index]--;
            iArr[i][index] += innerArr[i][dy][dx];
          }
          nums[dy][dx] = -1;
          getX[num - 1] = -1;
          getY[num - 1] = -1;
          vis &= ~(1LL << (num - 1));
        }
        if (!stk.empty()) tie(dx, dy, dnum, deleteNode) = stk.top();
      }
      continue;
    }

    stk.pop();
    if (org[y][x] == 0) {
      stk.push(make_tuple(x, y, num, true));
      if (nums[y][x] == -1) setNum(x, y, num);
    }

    if (vis == -1) {
      print();
      // verify();
      exit(0);
    }

    bool visNext = vis & (1LL << num++);
    for (l m = 0; m < 8; m++) {
      l x2 = x + dirX[m], y2 = y + dirY[m];
      if (x2 >= 0 && x2 < 8 && y2 >= 0 && y2 < 8 && ((visNext && nums[y2][x2] == num) || (!visNext && nums[y2][x2] == -1))) {
        bool isCan = true;
        if (!visNext) {
          for (l i = 0; i < 3; i++) {
            l index = indexArr[i][y2][x2];
            if (nArr[i][index] <= 2) {
              if (sumArr[i][index] + num >= 132) {
                isCan = false;
                break;
              }
            } else if (nArr[i][index] == 3) {
              if (i < 2) {
                l first = index & (~1LL), second = index | 1LL;
                if (sumArr[i][index] + num < 128 || sumArr[i][index] + num > 132 || (nArr[i][first] + nArr[i][second] == 7 && sumArr[i][first] + sumArr[i][second] + num != 260)) {
                  isCan = false;
                  break;
                }
              } else if (i == 2 && (sumArr[i][index] + num != 130)) {
                isCan = false;
                break;
              }
            }
          }
        }
        if (isCan) stk.push(make_tuple(x2, y2, num, false));
      }
    }
  }
}

* /