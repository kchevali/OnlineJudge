#include <iostream>
#include <string>
#include <cmath>
#include <functional>
#include <queue>
#include <fstream>

using namespace std;

//took a graph and return the MST, or don't return anything if just need the min cost

int mst(vector<vector<int>> adj, vector<tuple<int, int, int>> edge)
{
    int weight = 0;
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
            weight += w;
            visited[b] = true;
            for (auto x : adj[b])
            {
                tuple<int, int, int> n = edge[x];
                if (!visited[get<2>(n)])
                    pq.push(n);
            }
        }
    }
    return weight; //return MST
}

int main()
{

    int vertex;
    bool first = true;
    while (cin >> vertex)
    {
        if (first)
            first = false;
        else
            cout << endl;

        int c = 0;
        for (int i = vertex; i-- > 1;)
        {
            int a, b, w;
            cin >> a >> b >> w;
            c += w;
        }
        cout << c << endl;

        int index = 0;

        vector<vector<int>> adj(vertex, vector<int>());
        vector<tuple<int, int, int>> edge;

        for (int i = 2; i-- > 0;)
        {
            int count;
            for (cin >> count; count-- > 0;)
            {
                int a, b, w;

                cin >> a >> b >> w;
                a--;
                b--;
                edge.push_back(make_tuple(-w, a, b));
                adj[a].push_back(index++);
                edge.push_back(make_tuple(-w, b, a));
                adj[b].push_back(index++);
            }
        }
        cout << mst(adj, edge) << endl;
        cin.ignore();
        cin.ignore();
    }

    return 0;
}

/*



*/
