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
#define fpp(i, n) for (; i < n; i++)
#define fmm(i, n) while (i-- > n)
#define fpm(i, j, n) for (ll i = 0, j = (ll)n; j-- > 0; i++)
#define fa(it, arr) while (it++ != arr.end())

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef queue<int> qi;
typedef set<int> si;
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

vvi dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, 1}, {1, -1}};
map<vvll, ll> dp;
ll search(vvll v, int pegs, int sign)
{
    if (pegs == 1)
    {
        // cout << "Last PEG" << endl;

        return 0;
    }
    if (dp.count(v))
    {
        return sign * dp[v];
    }

    int i, j;

    ll max_diff = INT_INF;
    i = 0;
    fpp(i, v.size())
    {
        j = 0;
        fpp(j, v[i].size())
        {
            ll x = v[i][j];
            if (x == 0)
            {
                for (auto d : dir)
                {
                    int dx = d[0], dy = d[1];
                    int ex = j + 2 * dx, ey = i + 2 * dy;
                    if (ex >= 0 && ey >= 0 && ey < 5 && ex < 5 && v[i + dy][j + dx] > 0 && v[ey][ex] > 0)
                    {
                        // cout << "BEGIN: " << i << " " << j << " " << dx << " " << dy << endl;
                        ll prod = v[i + dy][j + dx] * v[ey][ex] * sign;
                        vvll copy = v;
                        copy[i][j] = copy[ey][ex];
                        copy[ey][ex] = 0;
                        copy[i + dy][j + dx] = 0;

                        ll sum = prod + search(copy, pegs - 1, sign * -1);
                        max_diff = sign * (max_diff == INT_INF ? sign * sum : max(sign * max_diff, sum * sign));
                    }
                }
            }
        }
    }
    // cout << "RETURNING" << endl;
    ll ans = max_diff == INT_INF ? 0 : max_diff;
    dp[v] = sign * ans;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int i, j, k;
    vvll v(5, vll(5, -1));

    i = 0;
    fpp(i, 5)
    {
        j = i + 1;
        k = 0;
        fmm(j, 0)
        {
            cin >> v[k++][j];
        }
    }
    ll ans = search(v, 14, 1);
    cout << ans << endl;

    return 0;
}

/*
0
0 0
0 0 0
5 0 0 0
3 0 0 0 0
15

0
0 0
9 0 0
5 0 0 0
3 0 0 0 0

20
0 1
0 0 0
1 0 0 0
10 0 0 1 30
20

1
2 3
4 5 6
7 8 9 10
11 12 13 14 15



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