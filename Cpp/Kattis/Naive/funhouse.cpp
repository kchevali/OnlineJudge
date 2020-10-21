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
#define in(x) cin >> x
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a

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

int x, y, dx, dy;

void swap(int sign)
{
    int dz = dy;
    dy = dx * sign;
    dx = dz * sign;
}

int main()
{
    int a, b, count = 1;
    in(a);
    in(b);

    while (a > 0)
    {
        cout << "HOUSE " << count++ << endl;
        vs v(b, string());
        for (int i = 0; i < b; i++)
        {
            in(v[i]);
            for (int j = 0; j < a; j++)
            {
                if (v[i][j] == '*')
                {
                    if (i == 0)
                    {
                        x = j;
                        y = 1;
                        dx = 0;
                        dy = 1;
                    }
                    else if (j == 0)
                    {
                        x = 1;
                        y = i;
                        dx = 1;
                        dy = 0;
                    }
                    else if (i == b - 1)
                    {
                        x = j;
                        y = b - 2;
                        dx = 0;
                        dy = -1;
                    }
                    else if (j == a - 1)
                    {
                        x = a - 2;
                        y = i;
                        dx = -1;
                        dy = 0;
                    }
                }
            }
        }
        while (x > 0 && x < a - 1 && y > 0 && y < b - 1)
        {
            if (v[y][x] == '/')
                swap(-1);
            else if (v[y][x] == '\\')
                swap(1);
            x += dx;
            y += dy;
        }
        v[y][x] = '&';
        for (auto vv : v)
            cout << vv << endl;

        in(a);
        in(b);
    }
    return 0;
}

/*



*/