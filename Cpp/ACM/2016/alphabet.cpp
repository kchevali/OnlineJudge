#include <bits/stdc++.h>

#define I_INF 0x3f3f3f3f
#define L_INF 0x3f3f3f3f3f3f3f3f
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
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)

#define con(x, a, b)     \
    if (x < a || x >= b) \
        cerr << "Out of Bounds: " << #x << endl;

using namespace std;

typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef queue<l> ql;
typedef pair<l, l> ll;
typedef pair<double, double> dd;
typedef set<l> sl;
typedef set<string> ss;
typedef map<l, l> ml;
typedef unordered_set<l> usl;
typedef unordered_map<l, l> uml;

l LIS(string array)
{
    vl dp(array.size(), 0);
    l i, j, mx = 0;
    fpp(i, 0, array.length())
    {
        fpp(j, i + 1, array.length()) if (array[j] > array[i])
            dp[j] = max(dp[j], dp[i] + 1);
        mx = max(mx, dp[i]);
    }
    return mx + 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    l a, b, c, x, y, z, n, m, i, j, k;

    string s;
    cin >> s;

    cout << (26 - LIS(s)) << endl;

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