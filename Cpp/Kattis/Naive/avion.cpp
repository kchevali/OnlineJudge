#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l count = 0;
  for(l i = 0; i < 5; i++){
    string s;
    cin >> s;
    if(s.find("FBI") < s.size()){
      cout << (i+1) << " ";
      count++;
    }
  }
  cout << (count ? "" : "HE GOT AWAY!") << "\n";
}
