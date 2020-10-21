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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x = 0;
    cin >> n;

    priority_queue<pii> q;
    mii m;
    vector<int> vis(n, 0);
    vector<int> v(n, 0);

    int i = 0;
    fpp(i, n)
    {
        cin >> v[i];
        m[v[i]] = i;
        vis[i] = i
    }

    i = 1;
    fpp(i, n)
    {
        q.push(mp(-max(v[i], v[i - 1]), min(v[i], v[i - 1])));
    }

    i = 0;
    fpp(i, n)
    {
        pii y = q.top();
        cout << y.fi << endl;
        q.pop();
        int a = m[abs(y.fi)], b = m[abs(y.se)] if (vis[a] == a && vis[b] == b)
                                  x += abs(q.top().fi);
    }
    cout << x << endl;

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