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
    vector<int> p, rank, setSize;
    int numSets;

    UF(int N)
    {
        p = vector<int>(N);
        rank = vector<int>(N);
        setSize = vector<int>(N);
        numSets = N;
        for (int i = 0; i < N; i++)
        {
            p[i] = i;
            rank[i] = 0;
            setSize[i] = 1;
        }
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

    // union two sets that contain element i and j
    void unionSet(int i, int j)
    {
        if (!isSameSet(i, j))
        {
            numSets--;
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y])
            {
                p[y] = x;
                setSize[x] = setSize[x] + setSize[y];
            }
            else
            {
                p[x] = y;
                setSize[y] = setSize[y] + setSize[x];
                if (rank[x] == rank[y])
                    rank[y] = rank[y] + 1;
            }
        }
    }

    // return number of disjoint sets
    int numDisjointSets()
    {
        return numSets;
    }

    // return the size of the set that contain element i
    int sizeOfSet(int i)
    {
        return setSize[findSet(i)];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    while (n > 0)
    {
        UF x = UF(n);
        int p = 0;
        fpp(p, m)
        {
            int k, i = 1, j;
            cin >> k >> j;
            fpp(i, k)
            {
                int q;
                cin >> q;
                x.unionSet(q, j);
            }
        }
        cout << x.sizeOfSet(0) << endl;
        cin >> n >> m;
    }

    return 0;
}