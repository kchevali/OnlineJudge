#include <bits/stdc++.h>
using namespace std;
typedef long long l;
typedef vector<string> vs;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string line, command, var, num, op;
  map<string, l> ints;
  map<l, string> vars;
  while (getline(cin, line)) {
    stringstream ss(line);
    ss >> command;
    // CLEAR
    if (command[1] == 'l') {
      ints = map<string, l>();
      vars = map<l, string>();
      continue;
    }
    // DEF
    if (command[0] == 'd') {
      ss >> var >> num;
      l x = stoll(num);
      if (ints.find(var) != ints.end()) {
        l old_val = ints[var];
        ints.erase(var);
        vars.erase(old_val);
      }
      ints[var] = x;
      vars[x] = var;
      continue;
    }

    // CALC
    l sum = 0, sign = 1;
    bool isUnknown = false;
    while (ss >> var >> op) {
      cout << var << " " << op << " ";

      if (isUnknown || ints.find(var) == ints.end()) {
        isUnknown = true;
      } else {
        sum += ints[var] * sign;
        sign = op[0] == '-' ? -1 : 1;
      }
    }
    cout << (isUnknown || vars.find(sum) == vars.end() ? "unknown" : vars[sum])
         << "\n";
  }
}