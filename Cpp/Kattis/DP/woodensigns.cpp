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

static l N = 2001;
static vvl dp(N, vl(N, -1));
static vl v(N, 0);

l search(l a, l b, l i)
{
    // cout << a << " " << b << " " << v[i] << endl;
    if (dp[a][b] != -1)
    {
        return dp[a][b];
    }
    if (i == N)
        return v[i] > a && v[i] < b ? 2 : 1;
    l sum = 0;
    if (v[i] > a)
    {
        sum += search(a, v[i], i + 1);
    }
    if (v[i] < b)
    {
        sum += search(v[i], b, i + 1);
    }
    return dp[a][b] = (sum % 2147483647LL);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    l i;

    cin >> N;

    fpp(i, 0, N + 1)
    {
        cin >> v[i];
    }
    cout << (N == 1 ? 1 : search(v[0], v[1], 2)) << endl;

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