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
#define debug(x) cout << #x << " -> " << x << '\n'
#define fpp(i, n) for (ll len = (ll)(n); i < len; ++i)
#define fmm(i, n) for (ll len = (ll)i, i = (ll)n; i-- > len;)
#define fpm(i, j, n) for (ll i = 0, j = (ll)n; j-- > 0; i++)
#define fa(it, arr) while (it++ != arr.end())

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
typedef vector<vector<bool>> vvb;
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

void print(vi &x)
{
    for (auto y : x)
    {
        cout << y << " ";
    }
    cout << endl;
}

int search(int x, vvi &v, vi &length, vi &pos, int index)
{
    if (length[x] != -1)
    {
        return length[x];
    }

    pos[index++] = x;

    int sum = 0;
    int i = 0;
    fpp(i, v[x].size())
    {
        int add = search(v[x][i], v, length, pos, index);
        index += add;
        sum += add;
    }
    return length[x] = (sum + 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vvi v(n, vi());
    int i = 0, j, k;

    fpp(i, n)
    {
        int x;
        cin >> x;
        if (x > 0)
        {
            v[x - 1].pb(i);
        }
    }

    vi length(n, -1), pos(n, -1);
    i = 0;
    fpp(i, n)
    {
        search(i, v, length, pos, 0);
    }
    vector<pii> pairs(n, pii());
    i = 0;
    fpp(i, n)
    {
        pairs[i].f = -length[i];
        pairs[i].s = i;
    }
    sort(pairs.begin(), pairs.end());

    vi temp(n, -1);
    int next = 0;
    i = 0;
    fpp(i, n)
    {
        int x = pairs[i].s;
        if (temp[x] == -1)
        {
            next += search(x, v, temp, pos, next);
        }
    }

    vi mp(n, 0);
    i = 0;
    fpp(i, n)
    {
        mp[pos[i]] = i;
    }

    // cout << "Length: ";
    // print(length);
    // cout << "Pos: ";
    // print(pos);
    // cout << "MP: ";
    // print(mp);

    int m;
    cin >> m;

    i = 0;
    fpp(i, m)
    {
        int p;
        cin >> p;

        int sum = 0;
        vector<pii> order(p, pii());
        j = 0;
        fpp(j, p)
        {
            int x;
            cin >> x;
            order[j].s = x - 1;
            order[j].f = -length[order[j].s];
        }
        sort(order.begin(), order.end());
        j = 0;
        fpp(j, p)
        {
            int x = order[j].s;
            bool good = true;

            k = 0;
            fpp(k, j)
            {
                int y = order[k].s;
                // cout << "Comp: " << x << " " << y << endl;
                if (mp[x] >= mp[y] && mp[x] < mp[y] + length[y])
                {
                    good = false;
                    break;
                }
            }
            if (good)
            {
                // cout << "Adding: " << x << endl;
                sum += length[x];
            }
        }
        cout << sum << endl;
    }
    // cout << "Done" << endl;
    return 0;
}

/*
2
0 0
3
1 1
1 2
2 1 2

5
0 1 2 3 4
8
1 5
1 1
2 1 2
2 1 5
5 4 2 5 1 3
2 4 5
1 3
1 2 5 4

1
0
1
10 1 1 1 1 1 1 1 1 1 1

6
3 4 5 5 0 5
7
1 1
1 2
1 6
1 5
3 5 1 4
3 1 3 2
3 6 4 1


*/