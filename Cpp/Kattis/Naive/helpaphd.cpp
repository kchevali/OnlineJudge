#include <bits/stdc++.h>
using namespace std;
typedef long long l;

void split(const string& s, const string& delim, string& a, string& b){
  size_t next = s.find(delim, 0);
  a = s.substr(0, next), b = s.substr(next, s.length());
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n;
  cin >> n;
  for(l i = 0; i < n ;i++){
    string s;
    cin >> s;
    if(s == "P=NP"){
      cout << "skipped\n";
      continue;
    }
    string x,y;
    split(s, "+", x, y);
    cout << (stoll(x) + stoll(y)) << "\n";
  }
}
