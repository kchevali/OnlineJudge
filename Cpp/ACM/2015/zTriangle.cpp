
#include "../all.cpp"

l py(l a, l b) { return a * a + b * b; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l a, b, c, x, y, z;
  cin >> a >> b >> c >> x >> y >> z;

  vl A{a, b, c};
  vl B{x, y, z};
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  cout << (A[2] == B[2] && A[0] == B[0] && A[1] == B[1] &&
                   py(A[0], A[1]) == A[2] * A[2]
               ? "YES"
               : "NO")
       << "\n";
}

/*
 39 52 65
 25 60 65

*/