#include <bits/stdc++.h>
using l = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l n;
    std::cin >> n;
    l arr[n];
    for(l i = 0; i < n; i++) std::cin >> arr[i];

    l total = 0, min = arr[n - 1];
    bool death = false;
    for(l i = n - 2; i >= 0; i--){
        // std::cerr << arr[i] << " P Min: " << min << "\n";
        if(arr[i] < min){
            min = arr[i];
        }else if (min <= 0){
            death = true;
            break;
        }else{
            min -= 1;
            total += arr[i] - min;
        }
    }
    std::cout << (death ? 1 : total) << "\n";
}
