#include <bits/stdc++.h>
using l = long long;

bool is_digit(std::string& s){
    for(char c: s){
        if(c < '0' || c > '9') return false;
    }
    return true;
}

void handle_var(std::string& var_name, std::unordered_map<std::string, l>& var_map, std::vector<std::string>& unknowns, l& total){
    if(is_digit(var_name)){ total += std::stoi(var_name); return; }
    auto it = var_map.find(var_name);
    if(it == var_map.end()) { unknowns.push_back(var_name); return; }
    total += it->second;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::unordered_map<std::string, l> var_map;

    std::string line;
    while(std::getline(std::cin, line)){
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while(ss >> token)tokens.push_back(token);

        if(tokens.size() == 1 && tokens[0].size() == 1 && tokens[0][0] == '0') break;

        l total = 0;
        if(tokens.size() > 1 && tokens[1][0] == '='){
            total = std::stoi(tokens[2]);
            auto it = var_map.find(tokens[0]);
            if(it != var_map.end()){
                it->second = total;
            }else{
                var_map.insert({tokens[0], total});
            }
            // std::cerr << tokens[0] << " = " << total << "\n";
        }else{
            std::vector<std::string> unknowns;
            for(l i = 0; i < tokens.size(); i+=2){
                handle_var(tokens[i], var_map, unknowns, total);
            }

            bool printed = total != 0 || unknowns.size() == 0;
            if(printed) std::cout << total;
            for(const auto& s: unknowns){
                if(printed)std::cout << " + ";
                std::cout << s;
                printed = true;
            }
            std::cout << "\n";
        }
    }
    // std::cerr << "done\n";
}
