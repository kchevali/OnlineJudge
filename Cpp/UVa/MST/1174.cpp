#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <vector>
#include <tuple>
#include <cmath>
#include <unordered_map>

using namespace std;
// Minium Spanning Tree

//took a graph and return the MST, or don't return anything if just need the min cost

int mst(vector<vector<int>> adj, vector<tuple<int, int, int>> edge)
{
    int mstWeight = 0;
    vector<bool> visited(adj.size(), false);
    visited[0] = true;
    priority_queue<tuple<int, int, int>> pq;
    for (auto x : adj[0])
        pq.push(edge[x]);

    while (!pq.empty())
    {
        tuple<int, int, int> t = pq.top();
        pq.pop();
        int w = abs(get<0>(t));
        int a = get<1>(t), b = get<2>(t);
        if (!visited[b])
        {
            mstWeight += w;
            visited[b] = true;
            for (auto x : adj[b])
            {
                tuple<int, int, int> n = edge[x];
                if (!visited[get<2>(n)])
                    pq.push(n);
            }
        }
    }
    return mstWeight; //return MST
}

int main()
{
    int cases, vertex;
    for (cin >> cases; cases-- > 0;)
    {
        cin.ignore();
        cin.ignore();
        cin >> vertex;

        int index = 0;
        vector<vector<int>> adj(vertex, vector<int>());
        vector<tuple<int, int, int>> edge;
        unordered_map<string, int> map;

        int count, city = 1;
        for (cin >> count; count-- > 0;)
        {
            int a, b, w;
            string as, bs;
            cin >> as >> bs >> w;
            a = (map[as] == 0 ? map[as] = city++ : map[as]) - 1;
            b = (map[bs] == 0 ? map[bs] = city++ : map[bs]) - 1;
            edge.push_back(make_tuple(-w, a, b));
            adj[a].push_back(index++);
            edge.push_back(make_tuple(-w, b, a));
            adj[b].push_back(index++);
        }
        cout << mst(adj, edge) << endl;
        if (cases > 0)
        {
            cout << endl;
        }
    }
}
