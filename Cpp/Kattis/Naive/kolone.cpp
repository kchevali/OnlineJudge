#include <iostream>
#include <string>
#include <cmath>
#include <functional>
#include <queue>
#include <fstream>

using namespace std;

int main()
{
    int a, b, t;
    string x, y, res = "";
    cin >> a >> b >> x >> y >> t;

    int i = a - 1, j = 0;
    if (t < a)
    {
        while (t++ < a)
            res += x[i--];
        res += y[j++];
    }
    else
        res = y.substr(0, j = t - a + 1);
    while (i >= 0 || j < b)
    {
        if (i >= 0)
            res += x[i--];
        if (j < b)
            res += y[j++];
    }
    cout << res << endl;
    return 0;
}

/*



*/