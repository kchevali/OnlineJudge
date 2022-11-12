#include <bits/stdc++.h>
using l = long long;

struct Vertex;
using Vertices = std::vector<Vertex*>;

const l inf = 0x3f3f3f3f3f3f3f3f;

struct Vertex {
    l t = 0, vis = 0;
    l depth = inf;
    Vertex const* parent = nullptr;
    Vertices adj;

    Vertex(l t): t(t){}
};

l bfs(Vertex* src, l max_depth) {
    std::queue<Vertex*> q;
    src->parent = src;
    src->depth = 0;
    src->vis = 1;
    q.push(src);
    l count = 0;

    while (!q.empty()) {
        const auto& a = q.front();
        q.pop();
        for (auto& b : a->adj) {
            count += b->vis == 0;
            b->vis += 1;
            if (b->vis >= b->t && a->depth + 1 < b->depth) {
                b->depth = a->depth + 1, b->parent = a;
                if(b->depth < max_depth) q.push(b);
            }
        }
    }
    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); 

    l n, m, d;
    std::cin >> n >> m >> d;

    if(d == 0 || n == 0 || m == 0){
        std::cout << "0\n";
        return 0;
    }

    Vertices vertices(n);

    std::unordered_map<std::string, Vertex*> mp;
    for(l i = 0; i < n; i++){
        std::string name;
        l t;
        std::cin >> name >> t;
        vertices[i] = new Vertex(t);
        mp[name] = vertices[i];
    }

    for(l i = 0; i < m; i++){
        std::string a, b;
        std::cin >> a >> b;
        const auto& va = mp[a], vb = mp[b];
        va->adj.push_back(vb);
        vb->adj.push_back(va);
    }

    std::string src;
    std::cin >> src;
    l res = bfs(mp[src], d);
    std::cout << res << "\n";

    // for(l i = 0; i < n; i++) delete vertices[i];
}