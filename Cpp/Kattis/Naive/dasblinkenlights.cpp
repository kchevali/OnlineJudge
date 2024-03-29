#include <bits/stdc++.h>
using namespace std;
typedef long long l;

l gcd(l a, l b) { return b == 0 ? a : gcd(b, a % b); }
l lcm(l a, l b) { return a * b / gcd(a, b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    l p, q, s;
    cin >> p >> q >> s;
    
    cout << (lcm(p, q) <= s ? "yes" : "no") << "\n";
}
