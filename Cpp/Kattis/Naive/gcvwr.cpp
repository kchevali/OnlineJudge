#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    l w, t, n;
    cin >> w >> t >> n;

    l tot = 0;
    for(l i = 0; i < n; i++){
        l x;
        cin >> x;
        tot += x;
    }
    cout << ((((w - t) * 9) / 10) - tot) << "\n";
}
