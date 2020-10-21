#include <iostream>
#include <vector>

using namespace std;

int aug(int left, vector<vector<int>> &adj, vector<int> &match, vector<bool> &visited)
{
    if (visited[left])
        return 0;
    visited[left] = true;

    for (auto right : adj[left])
    {
        if (match[right] == -1 || aug(match[right], adj, match, visited) == 1)
        {
            match[right] = left;
            return 1;
        }
    }

    return 0;
}

int getMatching(int v, int v_l, vector<vector<int>> adj)
{
    int count = 0;
    vector<int> match(v, -1);
    for (int i = v_l; i-- > 0;)
    {
        vector<bool> visited(v_l, false);
        count += aug(i, adj, match, visited);
    }
    return count;
}

int main()
{
    int n, m, t, v, d;
    while (cin >> n >> m >> t >> v)
    {
        d = v * v * t * t;
        vector<pair<double, double>> pos(n, pair<double, double>()), hole(m, pair<double, double>());
        vector<vector<int>> adj(n + m, vector<int>());
        for (int i = n; i-- > 0;)
        {
            cin >> pos[i].first >> pos[i].second;
        }
        for (int i = m; i-- > 0;)
        {
            cin >> hole[i].first >> hole[i].second;
        }

        for (int i = n; i-- > 0;)
        {
            for (int j = m; j-- > 0;)
            {
                double dx = pos[i].first - hole[j].first,
                       dy = pos[i].second - hole[j].second;
                if (dx * dx + dy * dy <= d)
                {
                    adj[i].push_back(j + n);
                }
            }
        }
        cout << (n - getMatching(n + m, m, adj)) << endl;
    }

    return 0;
}
/*

9 16 13 6
16.222222 8.394495
506.466667 236.028571
127.750000 82.933333
8.650000 13.100000
30.257732 30.935185
6.500000 8.100000
226.125000 35.500000
88.606061 53.427350
105.948276 67.800000
66.600000 69.363636
303.500000 107.333333
103.888889 59.470588
87.600000 81.272727
43.333333 52.500000
48.800000 29.611111
3.300000 4.812500
16.333333 10.812500
6.500000 4.437500
9.444444 9.888889
221.000000 156.666667
85.714286 57.250000
70.500000 107.000000
100.000000 24.600000
26.333333 27.555556
96.250000 56.125000

2









*/
