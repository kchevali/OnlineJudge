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

    char chh;
    cin >> chh;

    string s;
    cin >> s;

    char ch = s[0];
    if (chh == 'E')
    {
        int count = 1;
        int i = 1;
        fpp(i, s.length())
        {
            char c = s[i];
            if (ch == c)
            {
                count++;
            }
            else
            {
                cout << ch << count;
                count = 1;
                ch = c;
            }
        }
        cout << ch << count;
    }
    else
    {
        int i = 0;
        for (int i = 0; i < s.length(); i += 2)
        {
            int num = s[i + 1] - '0';
            int j = 0;
            fpp(j, num)
            {
                cout << s[i];
            }
        }
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

using namespace std;
*/