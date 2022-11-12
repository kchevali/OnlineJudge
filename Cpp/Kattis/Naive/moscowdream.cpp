#include <bits/stdc++.h>
using l = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l a, b, c, n;
    std::cin >> a >> b >> c >> n;
    std::cout << (a > 0 && b > 0 && c > 0 && n >= 3 && (a + b + c >= n) ? "YES" : "NO") << "\n";
}
