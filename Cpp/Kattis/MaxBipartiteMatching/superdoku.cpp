#include <bits/stdc++.h>

#define SHORT_INF 0x3f3f
#define INT_INF 0x3f3f3f3f
#define LL_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define l(x) x << 1
#define r(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define f first
#define s second
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a
#define db(x) cout << #x << " -> " << x << '\n'
#define fpp(i, n) for (ll len = (ll)(n); i < len; ++i)
#define fmm(i, n) for (ll len = (ll)i, i = (ll)n; i-- > len;)
#define fpm(i, j, n) for (ll i = 0, j = (ll)n; j-- > 0; i++)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef queue<int> qi;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef set<int> si;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

int aug(int left, vector<vector<int>> &adj, vector<int> &match, vector<bool> &visited)
{
    if (visited[left])
        return 0;
    visited[left] = true;

    for (auto right : adj[left])
    {
        if (right != -1)
        {
            if (match[right] == -1 || aug(match[right], adj, match, visited) == 1)
            {
                match[right] = left;
                return 1;
            }
        }
    }

    return 0;
}

vi getMatching(int v, int v_l, vector<vector<int>> adj)
{
    int count = 0;
    vector<int> match(v, -1);
    for (int i = v_l; i-- > 0;)
    {
        vector<bool> visited(v_l, false);
        count += aug(i, adj, match, visited);
    }
    return match;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    int i, j;
    vvi v(n, vi(n, 0));
    vvi g(n, vi(n, 0));

    vvi col(n, vi(n, 0));

    i = 0;
    fpp(i, n)
    {
        j = 0;
        fpp(j, n)
        {
            v[i][j] = j;
        }
    }
    i = 0;
    fpp(i, k)
    {
        vi row(n, 0);
        j = 0;
        fpp(j, n)
        {
            int a;
            cin >> a;

            a--;
            v[a][j] = -1;
            g[i][j] = a;

            if (row[a] + col[a][j] > 0)
            {
                cout << "no" << endl;
                return 0;
            }
            row[a] = 1;
            col[a][j] = 1;
        }
    }
    cout << "yes" << endl;
    i = k;
    fpp(i, n)
    {
        vi match = getMatching(n, n, v);
        j = 0;
        fpp(j, n)
        {
            v[match[j]][j] = -1;
            g[i][j] = match[j];
        }
    }
    for (auto x : g)
    {
        for (auto y : x)
        {
            cout << (y + 1) << " ";
        }
        cout << endl;
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