#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int w;
    cin >> w;
    while (w != 0)
    {
        int a, b, max_x = 0, max_y = 0, x = 0, y = 0;
        cin >> a >> b;
        while (a != -1)
        {
            if (a + x <= w)
            {
                x += a;
                if (x > max_x)
                    max_x = x;
                if (y + b > max_y)
                {
                    max_y = y + b;
                }
            }
            else
            {
                x = a;
                y = max_y;
                max_y += b;
            }
            cin >> a >> b;
        }
        cout << max_x << " x " << max_y << endl;
        cin >> w;
    }

    return 0;
}
