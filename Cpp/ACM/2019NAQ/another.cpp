#include <bits/stdc++.h> 
using namespace std; 
typedef long long l;

struct AhoCorasick{
    map<l,map<char,l>> go_to;
    vector<l> failure;
    map<l,vector<l>> output;
    vector<list<l>> positions;

    void create_goto(const vector<string> &patterns){
        l n = patterns.size(), new_state= 0;
        positions.resize(n);
        for(l i = 0;i < n; i++){
            l state = 0,j, m = patterns[i].size();
            for(j = 0; j < m && go_to[state].count(patterns[i][j]) >= 1; j++){
                state = go_to[state][patterns[i][j]];

            }
            for(l k = j; k < m; k++){
                go_to[state][patterns[i][k]] = ++new_state;
                state = new_state;
            }
            if(output.find(state) == output.end())output[state] = vector<l>(1,i);
            else output[state].emplace_back(i);
        }
        failure.resize(new_state+ 1 , 0);
        for(char i = ' '; i <= '~'; i++){
            if(go_to[0].count(i) == 0) go_to[0][i] = 0;
        }
        create_failure();
    }

    void create_failure(){
        queue<l> q;
        l current, state;
        for(auto it = go_to[0].begin(); it != go_to[0].end(); it++){
            if(it->second != 0){
                q.push(it->second);
                failure[it->second] = 0;
            }
        }
        while(!q.empty()){
            current = q.front();
            q.pop();
            state = failure[current];

            for(auto it = go_to[current].begin();it != go_to[current].end(); it++){
                if(go_to[current].count(it->first) != 0){
                    q.push(it-> second);
                    state = failure[current];
                    while(go_to[state].count(it->first) == 0){
                        state = failure[state];
                    }
                    failure[it->second] = go_to[state][it->first];
                    output[it -> second].insert(output[it->second].end(),output[failure[it->second]].begin(),output[failure[it->second]].end());
                }
            }
        }
    }

    void find_matches(const string &T){
        l state = 0, t, n = T.size();
        for( l i = 0; i < n; i++){
            while(go_to[state].count(T[i]) == 0){
                state = failure[state];
            }
            state = go_to[state][T[i]];
            if(output.count(state) > 0){
                t = output[state].size();
                vector<l> temp = output[state];
                for(l j = 0; j < t;j++){
                    positions[temp[j]].emplace_back(i);
                }
            }
        }
    }
};

int main(){
    l n = 4;
    AhoCorasick ac;
    vector<string> q(n);
    q[0] = "adab";
    q[1] = "dab";
    q[2] = "ab";
    q[3] = "z";

    string s = "abracadabra";
    ac.create_goto(q);
    ac.find_matches(s);
    l m = ac.positions.size();
    for(l i = 0 ; i < m; i++){
        for(auto it = ac.positions[i].begin(); it != ac.positions[i].end(); it++){
            printf("%llu ",*it-(q[i].size()-1));
        }
        printf("\n");
    }
    return 0;
}