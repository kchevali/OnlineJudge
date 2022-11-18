#include <bits/stdc++.h>
using l = long long;

struct Frequency {
    std::string word;
    l user_count = 0;
    l count = 0;

    Frequency(std::string word): word(word) {}
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::unordered_map<std::string, Frequency*> word_freq_map;
    std::unordered_map<std::string, std::unordered_map<std::string, l>> user_maps;

    l n;
    std::cin >> n;
    for(l i = 0; i < n; i++){
        std::string name, line;
        std::cin >> name;
        // std::cerr << "User: " << name << "\n";
        auto user_map_it = user_maps.find(name);
        if(user_map_it == user_maps.end()){
            // // std::cerr << "New User: " << name << "\n";
            user_maps.insert({name, {}});
        }
        auto& user_map = user_maps.find(name)->second;
        std::getline(std::cin, line);


        std::stringstream tokens(line);
        std::string token;
        while(tokens >> token){
            auto it = user_map.find(token);
            if(it != user_map.end()){
                it->second += 1;
                // // std::cerr << "Word: " << token << " -> " << it->second << "\n";
            }else{
                // // std::cerr << "New Word: " << token << "\n";
                user_map.insert({token, 1});
            }
        }
    }
    for(const auto& [user_name, user_map]: user_maps){
        for(const auto& [word, count]: user_map){
            // std::cerr << "- " << word << " -> " << count << "\n";
            auto it = word_freq_map.find(word);
            Frequency* f = nullptr;
            if(it != word_freq_map.end()){
                f = it->second;
            }else{
                // std::cerr << "New Frequency for: " << word << "\n";
                f = new Frequency(word);
                word_freq_map.insert({word, f});
            }
            f->user_count += 1;
            f->count += count;
        }
    }

    Frequency* all_user_words[word_freq_map.size()];

    l word_count = 0;
    // std::cerr << "Word Count: " << word_freq_map.size() << "\n";
    for(const auto& [word, f]: word_freq_map){
        // std::cerr << "User Count: " << word << " -> " << f->user_count << " : " << f->count << "\n";
        if(f->user_count < user_maps.size()) continue;
        all_user_words[word_count++] = f;
    }
    // std::cerr << "PASS Count: " << word_count << "\n";

    if(word_count == 0){
        std::cout << "ALL CLEAR\n";
        return 0;
    }

    std::sort(all_user_words, all_user_words + word_count, [](const auto a, const auto b) {
        // std::cerr << "SORT:" << a\n";
        return a->count == b->count ? a->word < b->word : a->count > b->count;
    });                                                                     
    // std::cerr << "PASS SORT\n";
    for(l i = 0; i < word_count; i++){
        std::cout << all_user_words[i]->word << "\n";
    }
    // std::cerr << "PASS READ\n";
}
