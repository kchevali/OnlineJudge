#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<int>::infinity()
#define pb push_back
#define mp make_pair
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define fi first
#define se second
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a
#define debug(x) cout << #x << " -> " << x << '\n'
#define fpp(i, n) for (ll len = (ll)(n); i < len; ++i)
#define fmm(i, n) for (ll len = (ll)i, i = (ll)n; i-- > len;)
#define fpm(i, j, n) for (ll i = 0, j = (ll)n; j-- > 0; i++)
#define fa(it, arr) while (it++ != arr.end())

#define con(x, a, b)     \
    if (x < a || x >= b) \
        cerr << "Out of Bounds: " << #x << endl;

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef vector<string> vs;
typedef vector<vector<string>> vvs;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
typedef vector<int> vd;
typedef vector<bool> vb;
typedef queue<int> qi;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<int, int> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef set<int> si;
typedef set<string> ss;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

//took a graph and return the MST, or don't return anything if just need the min cost

int mst(vector<vector<tuple<int, int, int>>> &edge, vector<pair<int, int>> &result)
{
    int weight = 0;
    vector<bool> visited(edge.size(), false);
    priority_queue<tuple<int, int, int>> pq;

    visited[0] = true;
    for (auto x : edge[0])
        pq.push(x);

    while (!pq.empty())
    {
        tuple<int, int, int> t = pq.top();
        pq.pop();

        int w = -get<0>(t);
        int a = get<1>(t), b = get<2>(t);

        if (!visited[b])
        {
            weight += w;
            result.push_back(make_pair(min(a, b), max(a, b))); //store the MST
            visited[b] = true;
            for (auto x : edge[b])
            {
                if (!visited[get<2>(x)])
                    pq.push(x);
            }
        }
    }
    sort(result.begin(), result.end());
    return weight; //return MST
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    int i, j;

    cin >> n >> m;
    while (n + m > 0)
    {
        vector<vector<tuple<int, int, int>>> edge(n, vector<tuple<int, int, int>>());

        i = 0;
        fpp(i, m)
        {
            int a, b, c;
            cin >> a >> b >> c;
            if (a != b)
            {
                edge[a].pb(make_tuple(-c, a, b));
                edge[b].pb(make_tuple(-c, b, a));
            }
        }

        vector<pair<int, int>> result;
        int weight = mst(edge, result);
        if (result.size() < n - 1)
            cout << "Impossible" << endl;
        else
        {
            cout << weight << endl;
            for (auto x : result)
                cout << x.fi << " " << x.se << endl;
        }
        // }

        cin >> n >> m;
    }

    return 0;
}

/*



*/

//Simple import
/*
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <string>
#include <queue>
#include <tuple>
#include <cmath>
#include <map>

using namespace std;
*/