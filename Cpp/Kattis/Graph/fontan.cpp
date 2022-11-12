#include <bits/stdc++.h>
using l = long long;

struct Vertex;
using Vertices = std::vector<Vertex*>;

const l inf = 0x3f3f3f3f3f3f3f3f;

struct Vertex {
    l value = 0;
    l depth = inf;
    Vertex const* parent = nullptr;
    Vertices adj;

    Vertex(char ch): value(ch == '.' ? 0 : (ch == 'V' ? 1 : -1)) {}
};

void bfs(Vertex* src) {
    std::queue<Vertex*> q;
    src->parent = src;
    src->depth = 0;
    q.push(src);

    while (!q.empty()) {
        const auto& a = q.front();
        q.pop();
        for (auto& b : a->adj) {
            if (a->depth + 1 < b->depth) {
                b->depth = a->depth + 1, b->parent = a, q.push(b);
                b->value = 1;
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l n, m;
    std::cin >> n >> m;

    std::vector<Vertices> grid(n, Vertices(m));

    for(l i = 0; i < n; i++){
        std::string line;
        std::cin >> line;

        for(l j = 0; j < m; j++){
            grid[i][j] = new Vertex(line[j]);
        }
    }

    for(l i = 0; i < n - 1; i++){
        for(l j = 0; j < m; j++){
            const auto& a = grid[i][j];
            if(a->value < 0) continue;

            const auto& b = grid[i+1][j];
            if(b->value < 0){
                if(j > 0){
                    const auto& left = grid[i][j-1];
                    if(left->value >= 0) a->adj.push_back(left);
                }
                if(j < m - 1){
                    const auto& right = grid[i][j+1];
                    if(right->value >= 0) a->adj.push_back(right);
                }
            }else{
                a->adj.push_back(b); // insert below
            }
        }
    }

    for(l i = 0; i < n; i++){
        for(l j = 0; j < m; j++){
            const auto& a = grid[i][j];
            if(a->value <= 0 || a->depth != inf) continue;
            bfs(a);
        }
    }

    char out[m + 1];
    out[m] = 0;
    for(l i = 0; i < n; i++){
        for(l j = 0; j < m; j++){
            const auto& a = grid[i][j];
            out[j] = a->value == 0 ? '.' : (a->value > 0 ? 'V' : '#');
        }
        printf("%s\n", out);
    }

}
