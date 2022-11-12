#include <bits/stdc++.h>
using l = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string nums;
    while(std::cin >> nums && nums[0] != 'E'){
        if(nums == "1"){
            std::cout << "1\n";
            continue;
        }
        l prev_length = 0, count = 1, length = nums.length();
        do{
            prev_length = length;
            nums = std::to_string(length);
            length = nums.length();
            ++count;
            
        }while(length != prev_length);
        std::cout << count << "\n";
    }
}
