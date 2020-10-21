#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
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
typedef vector<double> vd;
typedef vector<bool> vb;
typedef queue<int> qi;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
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

ll aug(int left, vector<vector<ll>> &adj, vector<ll> &match, vector<bool> &visited)
{
    // con(left, 0, visited.size());
    if (visited[left])
        return 0;
    visited[left] = true;

    // con(left, 0, adj.size());
    for (auto right : adj[left])
    {
        // con(right, 0, match.size());
        if (match[right] == -1 || aug(match[right], adj, match, visited) == 1)
        {
            match[right] = left;
            return 1;
        }
    }

    return 0;
}

int getMatching(int v_l, vector<vector<ll>> &adj, vll &match)
{
    ll count = 0;
    for (ll i = v_l; i-- > 0;)
    {
        vector<bool> visited(v_l, false);
        count += aug(i, adj, match, visited);
    }
    return count;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;

    int i;

    mlli mp;
    vector<pll> pr(n, pll());
    vvll adj(n, vll());

    i = 0;
    int index = 0, pos;
    fpp(i, n)
    {
        ll a, b;
        cin >> a >> b;
        pr[i].fi = a;
        pr[i].se = b;

        adj[i].pb(mp.count(a + b) ? mp[a + b] : (mp[a + b] = index++));
        if (a + b != a - b)
            adj[i].pb(mp.count(a - b) ? mp[a - b] : (mp[a - b] = index++));
        if (a + b != a * b && a - b != a * b)
            adj[i].pb(mp.count(a * b) ? mp[a * b] : (mp[a * b] = index++));
    }

    // cout << "ADJ" << endl;
    // for (auto x : adj)
    // {
    //     for (auto y : x)
    //     {
    //         cout << y << " ";
    //     }
    //     cout << endl;
    // }

    vll match(index, -1);
    int z = getMatching(n, adj, match);
    if (z != n)
    {
        cout << "impossible" << endl;
        return 0;
    }

    // cout << "MATCH" << endl;
    // for (auto x : match)
    // {
    //     cout << x << " ";
    // }
    // cout << endl;

    i = 0;
    fpp(i, n)
    {
        ll a = pr[i].fi, b = pr[i].se;
        string op;
        ll res;
        if (i == match[mp[res = a + b]])
        {
            op = " + ";
        }
        else if (i == match[mp[res = a - b]])
        {
            op = " - ";
        }
        else
        {
            op = " * ";
            res = a * b;
        }
        cout << a << op << b << " = " << res << endl;
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