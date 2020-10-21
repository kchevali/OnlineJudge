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

class UF
{
  public:
    vector<int> p, rank, enemy;

    UF(int N)
    {
        p = vector<int>(N);
        rank = vector<int>(N, 0);
        enemy = vi(N, -1);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }

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

    bool isEnemy(int i, int j)
    {
        return enemy[findSet(i)] == findSet(j);
    }

    void setEnemy(int i, int j)
    {
        int x = findSet(i), y = findSet(j);
        if (enemy[x] != -1)
        {
            unionSet(enemy[x], y, true);
            y = findSet(y);
        }
        if (enemy[y] != -1)
        {
            unionSet(enemy[y], x, true);
            x = findSet(x);
        }

        enemy[x] = y;
        enemy[y] = x;
    }

    void setRoot(int root, int branch, bool isEnemyJoin)
    {
        p[branch] = root;
        if (!isEnemyJoin && enemy[branch] != -1)
        {
            if (enemy[root] != -1)
                unionSet(enemy[root], enemy[branch], true);
            enemy[root] = findSet(enemy[branch]);
            enemy[enemy[root]] = root;
        }
    }

    // union two sets that contain element i and j
    void
    unionSet(int i, int j, bool isEnemyJoin)
    {
        if (!isSameSet(i, j))
        {
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y])
                setRoot(x, y, isEnemyJoin);
            else
            {
                setRoot(y, x, isEnemyJoin);

                if (rank[x] == rank[y])
                    rank[y] = rank[y] + 1;
            }
        }
    }

    void print()
    {
        cout << "\n\nMain: ";
        for (auto k : p)
        {
            cout << k << " ";
        }
        cout << endl
             << "Enemy: ";
        for (auto k : enemy)
        {
            cout << k << " ";
        }
        cout << endl;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    UF x = UF(n);
    int c, a, b;
    cin >> c >> a >> b;

    vi ans;
    while (c != 0)
    {
        switch (c)
        {
        case 1:
            if (x.isEnemy(a, b))
                ans.pb(-1);
            else
                x.unionSet(a, b, false);

            break;
        case 2:
            if (x.isSameSet(a, b))
                ans.pb(-1);
            else
                x.setEnemy(a, b);
            break;
        case 3:
            ans.pb(x.isSameSet(a, b));
            break;
        default:
            ans.pb(x.isEnemy(a, b));
        }
        // x.print();
        cin >> c >> a >> b;
    }

    for (auto z : ans)
    {
        cout << z << endl;
    }

    return 0;
}