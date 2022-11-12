#include <bits/stdc++.h>
using l = long long;
#define run_testcases(i, t) l t; std::cin >> t; for(l i = 0; i < t; i++)
namespace AllPairBFS{
    constexpr l N = 64;
    constexpr l inf = 0x3f3f3f3f3f3f3f3f;

    struct Vertex;
    struct VertexState {
        l depth = inf;
        Vertex* parent = nullptr;
    };

    using Vertices = std::vector<Vertex*>;
    struct Vertex {
        l idx = 0;
        VertexState states[N];
        Vertices adj;
        Vertex() {}
        Vertex(l idx): idx(idx) {}
    };

    void bfs(Vertex* src) {
        std::queue<Vertex*> q;
        auto& src_st = src->states[src->idx];
        src_st.parent = src;
        src_st.depth = 0;
        q.push(src);
        while (!q.empty()) {
            const auto& a = q.front();
            const auto& a_st = a->states[src->idx];
            q.pop();
            for (auto& b : a->adj) {
                auto& b_st = b->states[src->idx];
                if (a_st.depth + 1 < b_st.depth) {
                    b_st.depth = a_st.depth + 1, b_st.parent = a, q.push(b);
                }
            }
        }
    };
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    constexpr l side = 8;
    constexpr l N = side * side;
    AllPairBFS::Vertex vertices[N];

    l dirs[]{9, 7};
    for(l i = 0; i < N; i++){
        vertices[i].idx = i;
        for(const auto& dir: dirs){
            l j = i + dir;
            while(j < N) {
                if(((j / side) - (j - dir) / side) != 1 ) break;
                vertices[i].adj.push_back(vertices + j);
                vertices[j].adj.push_back(vertices + i);
                j += dir;
            }
        }
    }

    for(auto& src: vertices) AllPairBFS::bfs(&src);

    run_testcases(k, t){
        char c1, c2;
        l r1, r2;
        std::cin >> c1 >> r1 >> c2 >> r2;

        l i = N - r1 * side + c1 - 'A';
        l j = N - r2 * side + c2 - 'A';

        l depth = vertices[i].states[j].depth;  
        if(depth == AllPairBFS::inf){
            std::cout << "Impossible\n";
        }else{
            std::cout << depth;
            AllPairBFS::Vertex* prev = nullptr;
            auto parent = vertices + i;
            while(parent != prev){
                l p_idx = parent->idx;
                std::cout << ' ' << (char)(p_idx % side + 'A') << " " << (side - p_idx / side);
                prev = parent;
                parent = parent->states[j].parent;
            }
            std::cout << '\n';
        }
    }
}
