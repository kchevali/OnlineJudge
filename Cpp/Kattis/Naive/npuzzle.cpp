#include <bits/stdc++.h>
using l = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l total = 0;
    for(l i = 0; i < 4; i++){
        std::string s;
        std::cin >> s;
        for(l j = 0; j < 4; j++){
            if(s[j] == '.') continue;
            char ch = s[j] - 'A';
            // std::cerr << s[j] << " -> " << i << "~" << (ch / 4) << ", " << j << "~" << (ch % 4) << "\n";
            total += abs(i - (ch / 4)) + abs(j - (ch % 4));
        }
    }
    std::cout << total << "\n";
}
