#include <bits/stdc++.h>
using namespace std;
typedef long long l;

void split(const string& s, const string& delim, vector<string>& out){
  size_t last = 0; size_t next = 0;
  while ((next = s.find(delim, last)) != string::npos) {
    out.push_back(s.substr(last, next-last));
    last = next + 1;
  }
  out.push_back(s.substr(last));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  cin >> s;

  vector<string> v;
  split(s, ";", v);

  l total = 0;
  for(const string& ran: v){
    if(ran.find("-") < ran.length()){
      vector<string> nums;
      split(ran, "-", nums);
      total += stoll(nums[1]) - stoll(nums[0]) + 1;
    }else{
      total++;
    }
  }
  cout << total << '\n';
}
