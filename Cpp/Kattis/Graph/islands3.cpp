#include <bits/stdc++.h>
using l = long long;

// BFS: Unweighted - find path from one source
// Complexity O(V+E)
struct Vertex;
using Vertices = std::vector<Vertex*>;

const l inf = 0x3f3f3f3f3f3f3f3f;

struct Vertex {
    l value = 0;
    l depth = inf;
    Vertex const* parent = nullptr;
    Vertices adj;

    Vertex(char ch): value(ch == 'L' ? 0 : (ch == 'C' ? 1 : -1)) {}
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
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l n, m;
    std::cin >> n >> m;

    using VertixMatrix = std::vector<Vertices>;
    VertixMatrix grid(n, Vertices(m));

    for(l i = 0; i < n; i++){
        std::string line;
        std::cin >> line;
        for(l j = 0; j < m; j++){
            grid[i][j] = new Vertex(line[j]);
        }
    }

    l dirs[4][2]{
        {1,0}, {0,1}, {-1,0}, {0,-1}
    };

    for(l i = 0; i < n; i++){
        for(l j = 0; j < m; j++){
            const auto& a = grid[i][j];
            if(a->value < 0) continue;
            for(const auto& [dx, dy]: dirs){
                l x = j + dx;
                if(x < 0 || x >= m) continue;
                l y = i + dy;
                if(y < 0 || y >= n) continue;
                const auto& b = grid[y][x];
                if(b->value < 0) continue; // b.value cannot equal water
                a->adj.push_back(b);
            }
        }
    }

    for(l i = 0; i < n; i++){
        for(l j = 0; j < m; j++){
            const auto& a = grid[i][j];
            if(a->value < 0) continue;
            for(const auto [dx, dy]: dirs){
                l x = j + dx;
                if(x < 0 || x >= m) continue;
                l y = i + dy;
                if(y < 0 || y >= n) continue;
                const auto& b = grid[y][x];
                if(b->value < 0) continue; // b.value cannot equal water
                a->adj.push_back(b);
            }
        }
    }

    l count = 0;
    for(l i = 0; i < n; i++){
        for(l j = 0; j < m; j++){
            const auto& a = grid[i][j];
            if(a->value != 0 || a->depth != inf) continue;
            bfs(a);
            count++;
        }
    }
    std::cout << count << "\n";

    for(l i = 0; i < n; i++){
        for(l j = 0; j < m; j++){
            delete grid[i][j];
        }
    }
}
