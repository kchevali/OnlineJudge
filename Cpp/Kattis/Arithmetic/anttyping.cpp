#include <bits/stdc++.h>
using l = long long;

#define gc getchar_unlocked

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    constexpr l n = 9;

    l count[n][n];
    for(l i = 0; i < n; i++) for(l j = 0; j < n; j++) count[i][j] = 0;

    l nums[(l)1e5 + 10];
    l m = 0;
    char ch = gc();
    while(ch != '\n'){
        nums[m++] = ch - '1';
        ch = gc();
        // std::cerr << nums[m-1] << "\n";
    }
    for(l i = 1; i < m; i++){
        count[nums[i-1]][nums[i]] += 1;
    }

    // for(l i = 0; i < n; i++){
    //     for(l j = 0; j < n; j++){
    //         if(count[i][j] > 0)std::cerr << "C: " << (i + 1) << " " << (j + 1) << " -> " << count[i][j] << "\n";
    //     }
    // }

    l perm[]{0, 1, 2, 3, 4, 5, 6, 7, 8};

    l best = 1e18;
    std::string s;
    do{
        l total = 0;
        for(l i = 0; i < n; i++){
            if(perm[i] == nums[0]) total += (i + 1);
            // if(perm[i] == nums[m - 1]) total += (i + 1);
            for(l j = 0; j < n; j++){
                total += (abs(i - j) + 1) * count[perm[i]][perm[j]];
            }
        }
        if(total < best && total == 20){
            s = "";
            for(l p: perm) s += ('1' + p);

            // std::cerr << "BS: " << s << "\n";
            // std::cerr << "Best Score: " << total << "\n";
            // for(l i = 0; i < n; i++){
            //     if(perm[i] == nums[0]){
            //         std::cerr << "Cost to start:" << (i + 1) << "\n";
            //     }
            //     // if(perm[i] == nums[m - 1]){
            //     //     std::cerr << "Cost to end:" << (i + 1) << "\n";
            //     // }
            //     for(l j = 0; j < n; j++){
            //         if( count[perm[i]][perm[j]] > 0 )std::cerr << "Distance between " << (perm[i] + 1) << " & " << (perm[j] + 1) << " is " <<(abs(i - j) + 1) << " Count: " << count[perm[i]][perm[j]] << "\n";
            //     }
            // }
        }
        best = std::min(best, total);
    }while(std::next_permutation(perm, perm + n));
    std::cout << best << "\n";
    std::cerr << "BS: " << s << "\n";


}
