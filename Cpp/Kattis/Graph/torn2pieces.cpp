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

struct Node
{
    string name;
    vector<ll> edges; //target, weight = 1
    ll d = LL_INF / 2;
    ll prev = -1;
    ll index;
};

Node createNode(string name_, ll index_)
{
    Node n;
    n.name = name_;
    n.index = index_;
    return n;
}

bool dijkstra(ll source, ll dest, vector<Node> &v)
{
    priority_queue<pll> q;
    q.push(mp(v[source].d = 0, source));

    while (!q.empty())
    {
        ll a = q.top().s;
        q.pop();

        if (a == dest)
            return true;

        for (ll b : v[a].edges)
        {
            ll db = v[a].d + 1;
            // cout << a << " " << b << " | " << db << " " << v[b].d << endl;
            if (db < v[b].d)
            {
                v[b].prev = a;
                v[b].d = db;
                q.push(mp(db, b));
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
    cin.ignore();

    int i;

    map<string, ll> node_map;
    vector<Node> v;

    i = 0;
    fpp(i, n)
    {
        string line;
        getline(cin, line);
        stringstream strm(line);

        string a, b;

        strm >> a;
        if (!node_map.count(a))
        {
            node_map[a] = v.size();
            v.pb(createNode(a, v.size()));
        }

        ll ai = node_map[a];
        while (strm >> b)
        {
            if (!node_map.count(b))
            {
                node_map[b] = v.size();
                v.pb(createNode(b, v.size()));
            }
            ll bi = node_map[b];
            v[ai].edges.pb(bi);
            v[bi].edges.pb(ai);
        }
    }

    string src, des;
    cin >> src >> des;
    if (node_map.count(src) && node_map.count(des))
    {
        ll srci = node_map[src], desi = node_map[des];

        if (dijkstra(srci, desi, v))
        {
            stack<ll> st;
            ll curr = desi;
            while (curr != -1)
            {
                st.push(curr);
                curr = v[curr].prev;
            }
            while (!st.empty())
            {
                cout << v[st.top()].name << " ";
                st.pop();
            }
            cout << endl;
            return 0;
        }
    }
    cout << "no route found" << endl;

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