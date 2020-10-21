#include "../all.cpp"

// IMPORTS: typedef vector<string> vs; typedef pair<l, l> ll;
// typedef vector<ll> vll; typedef vector<l> vl;

// helper function
void huffman2(l index, string code, vll &child, vs &out) {
  if (child[index].first == -1) {
    out[index] = code;
  } else {
    huffman2(child[index].first, code + "0", child, out);
    huffman2(child[index].second, code + "1", child, out);
  }
}

// main function
vs huffman(vl &f) {
  priority_queue<ll, vector<ll>, greater<ll>> q;
  l i, n = f.size();
  vll v;
  for (l i = 0; i < n; i++) {
    q.push((ll){f[i], i});
    v.emplace_back((ll){-1, -1});
  }
  for (l i = 0; i < n - 1; i++) {
    l f = q.top().first;
    l a = q.top().second;
    q.pop();
    q.push((ll){f + q.top().first, v.size()});
    v.emplace_back((ll){a, q.top().second});
    q.pop();
  }
  vs out = vs(n);
  huffman2(q.top().second, "", v, out);
  return out;
}

int main() {
  vl v = {10000, 2, 2, 100};  // frequencies
  vs out = huffman(v);
  for (string s : out) cout << s << " ";
  cout << "\n";
  return 0;
}