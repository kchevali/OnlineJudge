using l = long long;

#include <vector>
#include <string>
#include <queue>

namespace Huffman {
  struct Pair {
    l freq, idx;
    Pair(l freq, l idx): freq(freq), idx(idx) {}
  };

  struct PairComp {
    bool operator() (const Pair& a, const Pair& b) {
    return a.freq > b.freq;
  }
};

  using Nums = std::vector<l>;
  using Pairs = std::vector<Pair>;
  using Strings = std::vector<std::string>;

  void printCode(l idx, std::string code, Pairs &child, Strings &out) {
    if (child[idx].freq == -1) {
      // std::cout << "C: " << idx << " " << code << "\n"; 
      out[idx] = code;
    } else {
      printCode(child[idx].freq, code + "0", child, out);
      printCode(child[idx].idx, code + "1", child, out);
    }
  }

  // main function
  Strings solve(Nums &freq) {
    std::priority_queue<Pair, Pairs, PairComp> q;
    auto n = freq.size();

    Pairs pairs;
    for (auto i = 0; i < n; i++) {
      q.push(Pair(freq[i], i));
      pairs.emplace_back(Pair(-1, -1));
      // std::cout << "PUSH: " << freq[i] << " @ " << i << "\n";
    }

    for (auto i = 0; i < n - 1; i++) {
      auto [freq, idx] = q.top();
      // std::cout << "Freq: " << freq << " Idx: " << idx << "\n";
      q.pop();
      auto [freq2, idx2] = q.top();
      q.pop();
      q.push(Pair(freq + freq2, pairs.size()));
      // std::cout << "--PUSH: " << (freq + freq2) << " @ " << pairs.size() << "\n";
      pairs.emplace_back(Pair(idx, idx2));
    }

    Strings out = Strings(n);
    printCode(q.top().idx, "", pairs, out);
    return out;
  }
}

#include <iostream>
int main() {
  Huffman::Nums v = {5, 1, 6, 3};  // frequencies
  auto out = Huffman::solve(v);
  for (auto &s : out) std::cout << s << ", ";
  std::cout << "\n";
  return 0;
}