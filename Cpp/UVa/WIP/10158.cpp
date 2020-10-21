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

    UF(int N)
    {
        p = vector<int>(N);
        rank = vector<int>(N, 0);
        setSize = vector<int>(N, 1);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }

    int findRoot(int i)
    {
        cout << "FINDING PARENT OF " << i << endl;
        cout << "PARENT: " << p[i] << endl;
        cout << "GRANDPARENT: " << p[p[i]] << endl;
        if (p[p[i]] == i)
        {
            return i;
            cout << "I AM GROUT" << endl;
        }
        else
        {
            int ret = findRoot(p[i]);
            p[i] = ret;
            cout << "Parent of " << i << " is " << ret << endl;
            return ret;
        }
    }

    // return true if element i and j are in the same set, return false otherwise
    bool isFriend(int i, int j)
    {
        return findRoot(i) == findRoot(j);
    }
    bool isEnemy(int i, int j)
    {
        int x = findRoot(i), y = findRoot(j);
        cout << "ROOTS: " << x << " " << y << endl;
        return p[x] == y && x != y;
    }

    // union two sets that contain element i and j
    void setFriend(int i, int j)
    {
        if (!isFriend(i, j))
        {
            int x = findRoot(i), y = findRoot(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y])
            {
                p[y] = x;
                setSize[x] = setSize[x] + setSize[y];
            }
            else
            {
                p[x] = y;
                if (rank[x] == rank[y])
                    rank[y] = rank[y] + 1;
            }
        }
    }
    void setEnemy(int i, int j)
    {
        if (!isEnemy(i, j))
        {
            int x = findRoot(i), y = findRoot(j);
            if (p[x] != x)
                p[p[x]] = y;
            if (p[y] != y)
                p[p[y]] = x;

            p[x] = y;
            p[y] = x;
            rank[x]++;
            rank[y]++;
        }
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
        cout << "HERE" << endl;
        switch (c)
        {
        case 1:
            cout << "BEGGGING" << endl;
            cout << "DATA: " << a << " " << b << endl;
            cout << "IS ENEMY: " << x.isEnemy(a, b) << endl;
            if (x.isEnemy(a, b))
                ans.push_back(-1);
            else
            {
                cout << "START" << endl;
                x.setFriend(a, b);
                cout << "END" << endl;
            }

            break;
        case 2:
            if (x.isFriend(a, b))
                ans.push_back(-1);
            else
                x.setEnemy(a, b);
            break;
        case 3:
            ans.push_back(x.isFriend(a, b));
            break;
        default:
            ans.push_back(x.isEnemy(a, b));
        }
        cout << "INPUT" << endl;
        cin >> c >> a >> b;
    }

    for (auto k : ans)
    {
        cout << k << endl;
    }

    cout << "FINAL" << endl;
    for (auto k : x.p)
    {
        cout << k << " ";
    }
    cout << endl;

    return 0;
}

/*
5
2 0 1
2 0 2
2 1 3
1 0 4
1 1 5
0 0 0

8
1 1 0
1 3 2
2 0 2
2 4 5
2 5 6
2 2 4
3 4 6
3 1 6
3 1 3
3 1 1
3 3 5
1 1 5
1 5 1
3 6 2
4 4 0
4 6 2
4 1 1
4 6 6
4 5 4
0 0 0

1
1
0
1
1
-1
-1
0
0
1
0
0
1

10
4 4 1
1 6 5
4 2 3
3 1 0
2 5 3
1 2 5
2 9 8
1 8 0
4 9 3
2 3 0
4 7 3
2 4 9
1 4 2
2 6 3
1 6 9
1 2 1
1 7 5
2 1 8
1 3 0
1 7 0
1 2 8
3 5 6
4 2 7
2 0 3
1 6 7
2 4 8
4 4 6
1 9 4
4 2 1
4 3 0
0 0 0

0
0
0
0
0
-1
-1
-1
1
0
-1
0
-1
0
1


*/