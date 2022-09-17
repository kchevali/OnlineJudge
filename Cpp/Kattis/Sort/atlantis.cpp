#include <bits/stdc++.h>
using namespace std;
typedef long long l;

typedef tuple<l,l> pt;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l n;
  cin >> n;
  pt pts[n];
  for(auto &[h, t]: pts){
    cin >> t >> h;
  }
  sort(pts, pts + n);
  priority_queue<l> q;

  l total = 0;
  for(l i = 0; i < n; i++){
    auto [h, t] = pts[i];
    q.push(t);
    total += t;

    
    while(!q.empty()){
      l x = q.top();
      if(total > h) total -= x, q.pop();
      else break;
    }
  }
  cout << q.size() << "\n";
}
