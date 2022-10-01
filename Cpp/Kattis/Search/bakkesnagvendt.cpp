#include <bits/stdc++.h>
using l = long long;

using StringIt = std::string::iterator;
using StringRevIt = std::string::reverse_iterator;
using Nums = std::vector<l>;

// PROBLEM STATUS: TLE - AC for 97 / 100

// match prefix is equal to suffix
// abcabcxabcabc -> ('', 'abc', 'abcabc')
inline void equal_prefix_suffix(const std::string& a, const std::string& b, l start, l end, l max_length, Nums& out){
    out.push_back(0);

    l fHash = 0LL, eHash = 0LL, x = 1LL, dx = 101LL;
    for(l i = start, j = end, k = 0; k < max_length; i++, j--, k++){
        fHash += a[i] * x;
        eHash = dx * eHash + b[j];
        x *= dx;
        // std::cerr << "Hash: " << fHash << " " << eHash << "\n";
        if(fHash != eHash || a[i] != b[end] || b[j] != a[start]) continue;
        out.push_back(i + 1);
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string x, y;
    std::cin >> x >> y;

    l n = x.length();

    l end = 0;
    for(end = n - 1; n >= 0 && x[end] == y[end]; --end);
    end++; // first d (if it has one)
    // std::cerr << "D:" << x.substr(end, n - end) << "\n";

    // front hash A, end hash A, mult A, delta mult
    Nums bestAs;
    equal_prefix_suffix(x, y, 0, end - 1, end, bestAs);

    for(l k = bestAs.size() -1; k >=0; k--){
        l bestA = bestAs[k];
        Nums bestBs;
        equal_prefix_suffix(x, y, bestA, end-1-bestA, end-bestA, bestBs);
        l bestB = bestBs[bestBs.size() - 1];
        // std::cerr << "B:" << x.substr(bestA, bestB - bestA) << "\n";
        // std::cerr << "C:" << x.substr(bestB, end-bestB) << "\n";
        bool match = true;
        for(l i = bestB, j = 0; i < end; i++, j++){
            if(x[i] != y[j]){
                match = false;
                break;
            }
        }
        if(match){
            std::cout << "1\n";
            return 0;
        }
    }
    std::cout << "0\n";
}
