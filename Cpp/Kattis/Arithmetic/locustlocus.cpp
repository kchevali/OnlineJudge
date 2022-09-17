#include <bits/stdc++.h>
using namespace std;
typedef long long l;

l gcd(l a, l b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    l n;
    cin >> n;
    l minV = 1e9;
    while(n--){
        l x, a, b;
        cin >> x >> a >> b;
        minV = min(minV, x + a * b / gcd(a, b));
    }
    cout << minV << "\n";
}
