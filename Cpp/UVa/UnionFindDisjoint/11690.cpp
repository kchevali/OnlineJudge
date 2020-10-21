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

#define MAXN 10000

vi p(MAXN), rnk(MAXN, 0), sum(MAXN, 0);

int findSet(int i)
{
    if (p[i] == i)
        return i;
    else
    {
        int ret = findSet(p[i]);
        p[i] = ret;
        return ret;
    }
}

// return true if element i and j are in the same set, return false otherwise
bool isSameSet(int i, int j)
{
    return findSet(i) == findSet(j);
}

// union two sets that contain element i and j
void unionSet(int i, int j)
{
    if (!isSameSet(i, j))
    {
        int x = findSet(i), y = findSet(j);
        // rnk is used to keep the tree short
        if (rnk[x] > rnk[y])
        {
            p[y] = x;
            sum[x] += sum[y];
        }
        else
        {
            p[x] = y;
            sum[y] = sum[y] + sum[x];
            if (rnk[x] == rnk[y])
                rnk[y] = rnk[y] + 1;
        }
    }
}

bool isZeroSum()
{
    for (auto i : p)
    {
        if (sum[findSet(i)] != 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int z;
    for (cin >> z; z-- > 0;)
    {
        int n, m;
        cin >> n >> m;
        int i = 0;
        fpp(i, n)
        {
            cin >> sum[i];
        }

        for (int k = 0; k < n; k++)
            p[k] = k;
        int j = 0;
        fpp(j, m)
        {
            int a, b;
            cin >> a >> b;
            unionSet(a, b);
        }

        cout << (isZeroSum() ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    }
    return 0;
}