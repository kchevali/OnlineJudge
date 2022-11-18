#include <bits/stdc++.h>
using l = long long;

struct Seat{
    l idx;
    l num;
    Seat(l idx, l num): idx(idx), num(num) {}
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l n;
    std::cin >> n;
    Seat* seats[n];
    for(l i = 0; i < n; i++){
        l x;
        std::cin >> x;
        seats[i] = new Seat(i, x);
    }

    std::sort(seats, seats+n, [](const auto a, const auto b){
        return a->num == b->num ? a->idx < b->idx : a->num < b->num;
    });

    l awk = n;
    for(l i = 1; i < n; i++){
        if(seats[i]->num != seats[i-1]->num) continue;
        awk = std::min(awk, seats[i]->idx - seats[i - 1]->idx);
    }
    std::cout << awk << "\n";
}
