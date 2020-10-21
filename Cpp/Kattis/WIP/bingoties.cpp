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
typedef vector<ll> vll;
typedef vector<double> vd;
typedef vector<vector<int>> vvi;
typedef set<int> si;
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

//CHECK: Proper prefix algorithm

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int z;
    cin >> z;

    vvi v(z, vi(25, 0));
    vector<mii> rows;
    si collect, match;

    int i, j, k, p, q;

    i = 0;
    fpp(i, z) //every card
    {
        mii row;

        j = 0;
        fpp(j, 25) //every number
        {
            int a;
            cin >> a;

            v[i][j] = a;
            row[a] = j / 5;

            if (collect.count(a))
            {
                match.insert(a);
                // cout << "Card: " << j << " Num: " << i << " Match: " << a << endl;
            }
            collect.insert(a);
        }
        rows.pb(row);
    }
    if (match.size() == 0)
    {
        cout << "no ties" << endl;
        return 0;
    }
    // cout << "Got all Matches: " << match.size() << endl;
    vi shortest(9, 0);
    int length = 9;
    int a, b;

    auto it = match.begin();
    fa(it, match) //every match
    {
        int x = *it;
        i = 0;

        fpp(i, z)
        {
            int r1 = rows[i][x];
            j = i + 1;

            fpp(j, z)
            {
                int r2 = rows[j][x];
                si st;
                k = 0;
                fpp(k, 5)
                {
                    st.insert(v[i][k + r1]);
                }
                k = 0;
                fpp(k, 5)
                {
                    st.insert(v[i][k + r2]);
                }
                // cout << i << "(" << r1 << ") " << j << "(" << r2 << ") ~ " << st.size() << " -- " << length << endl;
                if (st.size() < length)
                {
                    a = i;
                    b = j;
                    // cout << "A: " << a << " B: " << st.size() << endl;
                    length = st.size();
                    int index = 0;
                    auto it2 = st.begin();
                    fa(it2, st)
                    {
                        shortest[index++] = *it2;
                    }
                }
            }
        }
    }

    i = 0;
    fpp(i, z)
    {
        j = 0;
        fpp(j, 5)
        {
            int count = 0;
            k = 0;
            fpp(k, 5)
            {
                p = 0;
                fpp(p, length)
                {
                    if (shortest[p] != v[i][j * 5 + k])
                    {
                        count = -100;
                        break;
                    }
                    count++;
                }
            }
            if (count == 5)
            {
                cout << "no ties" << endl;
                return 0;
            }
        }
    }

    cout << (a + 1) << " " << (b + 1) << endl;
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