#include "../all.cpp"  //24 minutes
typedef vector<pair<string, string>> vss;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  l n;
  cin >> n;
  cin.ignore();
  l i, j;
  vss ranks(n);
  l count = 0;
  fpp(i, 0, n) {
    string line, name, token;
    j = 0;
    getline(cin, line);
    stringstream ss(line);
    ss >> name;
    ranks[i].second = name.substr(0, name.length() - 1);
    // db(ranks[i].second);
    l c = 0;
    while (ss >> token) {
      if (token == "class") break;
      ranks[i].first = token[0] + ranks[i].first;
      c++;
    }
    // db(ranks[i].first);

    j++;
    count = max(count, c);
  }
  fpp(i, 0, n) {
    // cout << "Class: " << ranks[i].first << "\n";
    while (ranks[i].first.length() < count) ranks[i].first += 'm';
  }

  sort(ranks.begin(), ranks.end(), [](const ss &a, const ss &b) {
    return a.first == b.first ? a.second > b.second : a.first < b.first;
  });
  fmm(i, 0, n) { cout << ranks[i].second << "\n"; }
}
