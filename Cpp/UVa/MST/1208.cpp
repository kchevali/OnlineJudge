#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;
// Minium Spanning Tree

vector<tuple<int, int, int>> mst(vector<vector<int>> adj, vector<tuple<int, int, int>> edge)
{
    vector<tuple<int, int, int>> result; //store the MST
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
            result.push_back(make_tuple(w, min(a, b), max(a, b))); //store the MST
            visited[b] = true;
            for (auto x : adj[b])
            {
                tuple<int, int, int> n = edge[x];
                if (!visited[get<2>(n)])
                    pq.push(n);
            }
        }
    }
    return result; //return MST
}

int main()
{
    int cases, vertex;
    cin >> cases;
    for (int z = 1; z <= cases; z++)
    {
        cout << "Cases " << z << ":" << endl;
        cin >> vertex;
        vector<vector<int>> adj(vertex, vector<int>());
        vector<tuple<int, int, int>> edge;

        int index = 0;
        for (int i = 0; i < vertex; i++)
        {
            for (int j = 0; j < vertex; j++)
            {
                string ws;
                cin >> ws;
                if (ws[0] != '0')
                {
                    int w = stoi(j == vertex - 1 ? ws : ws.substr(0, ws.length() - 1));
                    edge.push_back(make_tuple(-w, i, j));
                    adj[i].push_back(index++);
                    edge.push_back(make_tuple(-w, j, i));
                    adj[j].push_back(index++);
                }
            }
        }
        vector<tuple<int, int, int>> result = mst(adj, edge);
        sort(result.begin(), result.end());
        for (auto p : result)
        {
            cout << (char)('A' + get<1>(p)) << "-" << (char)('A' + get<2>(p)) << " " << get<0>(p) << endl;
        }
    }
}