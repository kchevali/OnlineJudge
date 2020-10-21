#include <bits/stdc++.h>

#define I_INF 0x3f3f3f3f
#define L_INF 0x3f3f3f3f3f3f3f3f
#define D_INF numeric_limits<double>::infinity()
#define pb push_back
#define mp make_pair
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define mid(x, y) x + (y - x) / 2
#define fi first
#define se second
#define Fill(a, x) memset(a, x, sizeof(a))
#define randi(a, b) rand() % (b - a + 1) + a
#define debug(x) cout << #x << " -> " << x << '\n'
#define fpp(i, a, b) for (i = a; i < b; i++)
#define fmm(i, a, b) for (i = b; i-- > a;)

#define con(x, a, b)     \
    if (x < a || x >= b) \
        cerr << "Out of Bounds: " << #x << endl;

using namespace std;

typedef long long l;
typedef vector<l> vl;
typedef vector<vl> vvl;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef pair<l, l> ll;
typedef pair<double, double> dd;
typedef queue<l> ql;
typedef priority_queue<ll, vector<ll>, greater<ll>> pql;
typedef set<l> sl;
typedef set<string> ss;
typedef map<l, l> ml;
typedef unordered_set<l> usl;
typedef unordered_map<l, l> uml;

l dijkstra(l aa, l bb, vvl &adj, vvl &wt, stack<l> &path) //start, end, adj[a][i], w[a][b]
{
    vl dis(adj.size(), L_INF), prev(adj.size(), -1);
    pql q;
    q.push(mp(dis[aa] = 0, aa));
    while (!q.empty())
    {
        ll p = q.top();
        q.pop();
        l a = p.se;
        if (a == bb)
        {
            l d = dis[a];
            do
            {
                wt[a][prev[a]] *= -1;
                path.push(a);
                a = prev[a];
            } while (prev[a] != -1);
            return d;
        }
        for (l b : adj[a])
        {
            if (wt[a][b] <= 0)
                continue;
            l d = dis[a] + wt[b][a];
            if (d >= dis[b])
                continue;
            prev[b] = a;
            q.push(mp(dis[b] = d, b));
        }
    }
    return -1;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    l n, m, i;

    cin >> n;
    while (n > 0)
    {
        cin >> m;
        vvl adj(n, vl()), wt(n, vl(n, L_INF));
        stack<l> path;
        fpp(i, 0, m)
        {
            l a, b, w;
            cin >> a >> b >> w;
            adj[--a].pb(--b);
            adj[b].pb(a);
            wt[a][b] = w;
            wt[b][a] = w;
        }
        l a = dijkstra(0, n - 1, adj, wt, path);
        l b = dijkstra(n - 1, 0, adj, wt, path);
        if (a < 0 || b < 0)
        {
            cout << "Back to jail" << endl;
        }
        else
        {
            cout << (a + b) << endl;
        }
        cin >> n;
    }
    return 0;
}

/*
6
8
1 2 1
2 3 1
3 6 1
1 4 100
4 5 100
5 6 100
1 3 10
2 6 10
0

22



*/