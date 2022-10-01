#include <bits/stdc++.h>
using l = long long;

inline double getVolume(double a, double b, double x, double y){
    auto h = std::min(x-a, y-b) / 2.0;
    return a * b * h;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    l t;
    std::cin >> t;
    for(l i = 0; i < t; i++){
        double x, y;
        std::cin >> x >> y;

        double a = 12;
        double b = (-4.0) * x + (-4.0) * y;
        double c = x * y;

        double delta = sqrt(b * b - 4 * a * c);
        double hs[]{(-b-delta) / (2 * a), (-b+delta) / (2 * a)};
        // double minH = 0.0;
        // double maxH = std::fmin(x, y) / 2;
        // double delta = (maxH - minH) / 10'000.0;

        double maxv = 0.0;
        for(double h: hs){
            // std::cout << "H: " << h << "\n";
            double v = (x - 2 * h) * (y - 2 * h) * h;
            if(v > maxv){
                maxv = v;
            }
        }
        std::cout << std::setprecision(10) << maxv << "\n";
    }
}
