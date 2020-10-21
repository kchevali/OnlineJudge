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
#define fa(it, arr) while (it++ != arr.end())

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

int getRow(vvi v, int num)
{
    int i, j;
    i = 0;
    fpp(i, v.size())
    {
        j = 0;
        fpp(j, v[i].size())
        {
            if (v[i][j] == num)
            {
                return i / 5;
            }
        }
    }
}

bool findWin(vector<vvi> &v, si &rows, int a, int b, int n)
{
    int i, j, k;
    i = 0;
    fpp(i, n)
    {
        if (i != a && i != b)
        {
            j = 0;
            fpp(j, 5)
            {
                bool match = true;
                k = 0;
                fpp(k, 5)
                {
                    if (!rows.count(v[i][j][k]))
                    {
                        match = false;
                    }
                }
                if (match)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int i, j, k, m, p;

    si all, num;
    vector<si> cards;
    vector<vvi> v(n, vvi(5, vi(5, 0)));

    i = 0;
    fpp(i, n)
    {
        si card;
        j = 0;
        fpp(j, 5)
        {
            k = 0;
            fpp(k, 5)
            {
                int a;
                cin >> a;
                v[i][j][k] = a;

                if (all.count(a))
                {
                    num.insert(a);
                }
                all.insert(a);
                card.insert(a);
            }
        }
        cards.pb(card);
    }
    if (num.size() > 0)
    {
        i = 0;
        fpp(i, n)
        {
            j = 1;
            fpp(j, n)
            {
                auto it = num.begin();
                fa(it, num)
                {
                    int x = *it;
                    if (cards[i].count(x) && cards[j].count(x))
                    {

                        int a = getRow(v[i], x);
                        int b = getRow(v[j], x);
                        si rows;
                        for (auto x : v[i][a])
                            rows.insert(x);
                        for (auto x : v[j][b])
                            rows.insert(x);
                        if (!findWin(v, rows, i, j, n))
                        {
                            cout << (i + 1) << " " << (j + 1) << endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    cout << "no ties" << endl;
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