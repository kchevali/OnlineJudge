#include <bits/stdc++.h>
#define PB emplace_back
#define C cout <<
#define E << "\n"
#define _ << " " <<
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)
using namespace std;
typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

    double x, y;
    l c,test = 1, i;
  while(cin >> x >> y >> c){
        double a = 0, b = 0;
        bool done = false;
        fpp(i,0,c){
            double a1 = a*a - b*b + x;
            double b1 = 2*a*b + y;
            if(a1*a1 + b1*b1 > 4){
                done = true;
                break;
            }
            a = a1;
            b = b1;
        }
        C "Case" _ (test++) << ":" _ (done ? "OUT" : "IN") E;
  }
}
