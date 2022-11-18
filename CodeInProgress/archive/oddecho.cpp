#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    l n;
    cin >> n;

    for(l i = 0 ; i < n; i++){
        string s;
        cin >> s;
        if((i & 1) == 0) cout << s << "\n";
    }
}
