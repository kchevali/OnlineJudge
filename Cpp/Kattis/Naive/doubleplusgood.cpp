#include <bits/stdc++.h>
using l = long long;

using Strings = std::vector<std::string>;
Strings split(const std::string& s, char delim){
  std::stringstream test(s);
  std::string segment;
  Strings seglist;

  while(std::getline(test, segment, delim))
  {
    seglist.push_back(segment);
  }
  return seglist;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string equ;
    std::cin >> equ;

    Strings tokens = split(equ, '+');
    l n = tokens.size();
    l m = n - 1;

    l nums[n];
    for(l i = 0; i < n; i++){
        // std::cerr << token << "\n";
        nums[i] = stoll(tokens[i]);
        // std::cerr << nums[i] + 1 << "\n";
    }

    l bf = (1LL << m);

    std::unordered_set<l> ans;

    for(l i = 0; i < bf; i++){
        l concat = nums[n - 1], total = 0;
        // std::cerr << "IM: " << mult << "\n";
        // std::cerr << nums[n-1];
        for(l j = 1; j < n; j++){
            l num = nums[n - 1 - j];
            if(((i >> (j-1)) & 1) == 0){
                //addition
                // std::cerr << " + ";
                total += concat;
                concat = num;
            }else{
                // int concat
                // std::cerr << " * ";
                l tmp = num, tconcat = concat;
                do tmp *= 10; while(tconcat /= 10);
                concat += tmp;
            }
            // std::cerr << num;
            // std::cerr << "\nTotal: " << total << " Concat: " << concat << "\n";
        }
        total += concat;
        ans.insert(total);
        // std::cerr << " = " << total << "\n";
        // if(i == 1)break;
    }
    std::cout << ans.size() << "\n";
}
