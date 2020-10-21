#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef pair<l, l> ll;
typedef priority_queue<ll, vector<ll>, less<ll>> pqll;  // max first

int main() {
  l n, t, money, endTime, x = 0;
  cin >> n >> t;
  l times[t];
  memset(times, 0, sizeof times);
  pqll q;
  for (l i = 0; i < n; i++) {
    cin >> money >> endTime;
    q.push(make_pair(money, endTime));
  }
  while (!q.empty()) {
    tie(money, endTime) = q.top();
    q.pop();
    l minIndex = -1, minValue = money;
    for (l i = endTime; i >= 0; i--)
      if (times[i] < minValue) minValue = times[minIndex = i];

    if (minIndex == -1) continue;
    x += money - times[minIndex];
    times[minIndex] = money;
  }
  cout << x << "\n";
}