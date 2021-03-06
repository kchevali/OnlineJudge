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
typedef vector<ll> vll;
typedef vector<double> vd;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<llu, llu> pllu;
typedef map<int, int> mii;
typedef map<int, ll> mill;
typedef map<ll, int> mlli;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, ll> umill;
typedef unordered_map<ll, int> umlli;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string s;
    cin >> n >> s;

    vi v(n, 0);

    int i = 0;
    for (; i < n - 1; i++)
    {
        if (s[i] == 'R')
            v[i] = i + 1;
        else
        {
            int j = i + 1;
            while (j < n - 1 && s[j] == 'L')
                j++;
            int k = 1;
            while (i <= j)
            {
                v[j] = i + k;
                j--;
                k++;
            }
            i += k - 2;
        }
    }
    if (s[s.length() - 1] == 'R')
        v[n - 1] = n;

    for (auto x : v)
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

using namespace std;
*/