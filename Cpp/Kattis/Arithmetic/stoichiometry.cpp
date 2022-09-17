#include <bits/stdc++.h>
using namespace std;
typedef long long l;

// solve Linear Equations
class LinearEquations {
 public:
  static const l length = 20;

  double a[length][length];
  double sol[length];

  // flag == 0 for No solution
  // flag == 1 for One Solution
  // else for infinite solution
  l gaussJordanElimination(l n) {
    // Performing elementary operations
    l flag = 1;
    for (l i = 0; i < n; i++) {
      if (a[i][i] == 0) {
        l c = 1;
        while (i + c < n && a[i + c][i] == 0) c++;
        if (i + c == n) {
          flag = 0;
          break;
        }
        for (l j = i, k = 0; k <= n; k++) swap(a[j][k], a[j + c][k]);
      }

      // Form Diagnoal
      for (l j = 0; j < n; j++) {
        if (i != j) {
          double pro = a[j][i] / a[i][i];
          for (l k = 0; k <= n; k++) a[j][k] -= a[i][k] * pro;
        }
      }
    }

    if (flag == 0) {
      for (l i = 0; i < n; i++) {
        double sum = 0;
        for (l j = 0; j < n; j++) sum += a[i][j];
        if (sum == a[i][n]) flag = 2;
      }
    }
    for (l i = 0; i < n; i++) sol[i] = a[i][n] / a[i][i];
    return flag;
  }

  double* operator[](l i) { return a[i]; }
};

void makeint(double* arr, l length){
  double frac = 1.0;
  for(l i = 0; i < length; i++){
    double fracPart, intPart;
    fracPart = modf(arr[i], &intPart);
    if(fracPart > 1e-6) frac = min(frac, fracPart);
  }
  for(l i = 0; i < length; i++){
    arr[i] /= frac;
  }
  if(abs(frac - 1.0) > 1e-6)makeint(arr, length);
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  LinearEquations eq;
  unordered_map<string, l> ids;

  memset(eq.a, 0, sizeof(eq.a));
  memset(eq.sol, 0, sizeof(eq.sol));

  l s, m, n = 0, j = 0;
  for(;cin >> s >> m && s != 0 && m != 0; j++){
    for(l i = 0; i < m; i++){
      string name;
      l count;
      cin >> name >> count;

      if(ids.find(name) == ids.end()) ids[name] = n++;
      l id = ids[name];

      eq[id][j] += s * count;
    }
  }
  l size = max(n, j) + 1;  
  eq[size-1][0] = 1;
  eq[size-1][size] = 1;

  l sts = eq.gaussJordanElimination(size);
  makeint(eq.sol, j);
  for(l i = 0; i < j; i++)cout << eq.sol[i] << " ";
      cout << "\n";
  
}
