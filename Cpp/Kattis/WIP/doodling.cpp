#include <bits/stdc++.h>
using namespace std;
typedef long long l;

l gcd(l a, l b) { return b == 0 ? a : gcd(b, a % b); }
l lcm(l a, l b) { return a * b / gcd(a, b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    l n;
    cin >> n;
    while(n--){
        l a, b;
        cin >> a >> b;
        cout << lcm(a, b) << "\n";

    }
}
