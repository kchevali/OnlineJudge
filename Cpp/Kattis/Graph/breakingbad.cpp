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

bool search(vvi &v, vi &mark, vvi &group, int x, int sign)
{
    for (auto y : v[x])
    {
        if (mark[y] + sign == 0)
        {
            return false;
        }
        else if (mark[y] == 0)
        {
            mark[y] = sign;
            group[(sign + 1) / 2].pb(y);
            if (!search(v, mark, group, y, -sign))
            {
                return false;
            }
        }
    }
    return true;
}

int main() //algorithm idea: check for odd cycles
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int i;

    map<string, int> antro;
    vs retro(n, "");

    i = 0;
    fpp(i, n)
    {
        string s;
        cin >> s;
        antro[s] = i;
        retro[i] = s;
    }

    int m;
    cin >> m;

    vvi v(n, vi());

    i = 0;
    fpp(i, m)
    {
        string a, b;
        cin >> a >> b;

        int ai = antro[a], bi = antro[b];

        v[ai].pb(bi);
        v[bi].pb(ai);
    }

    vi mark(n, 0);
    vvi group(2, vi());

    i = 0;
    fpp(i, n)
    {
        if (mark[i] == 0 && !search(v, mark, group, i, 1))
        {
            cout << "impossible" << endl;
            return 0;
        }
    }

    i = 0;
    fpp(i, n)
    {
        if (mark[i] == 0)
        {
            cout << retro[i] << " ";
        }
    }
    for (auto x : group)
    {
        for (auto y : x)
        {
            cout << retro[y] << " ";
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