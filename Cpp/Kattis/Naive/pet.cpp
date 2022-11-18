#include <bits/stdc++.h>
using l = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l best = 0, user = -1;
    for(l i = 0; i < 5; i++){
        l total = 0;
        for(l j = 0; j < 4; j++){
            l x;
            std::cin >> x;
            total += x;
        }
        if(total > best){
            user = i;
            best = total;
        }
    }
    std::cout << (user + 1) << " " << best << "\n";
}
