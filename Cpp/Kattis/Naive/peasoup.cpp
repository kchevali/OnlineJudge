#include <bits/stdc++.h>
using l = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l n;
    std::cin >> n;

    bool done = false;
    for(l i = 0; i < n; i++) {
        l m;
        std::cin >> m;
        std::cin.ignore();
        bool pancakes = false, peasoup = false;

        std::string place;
        getline(std::cin, place);

        for(l j = 0; j < m; j++){
            std::string line;
            std::getline(std::cin, line);
            // std::cerr << place << " " << line << "\n";

            if(line == "pancakes") pancakes = true;
            else if(line == "pea soup") peasoup = true;
        }
        if(!done && pancakes && peasoup){
            done = true;
            std::cout << place << "\n";
        }
    }

    if(!done) std::cout << "Anywhere is fine I guess\n";
}
