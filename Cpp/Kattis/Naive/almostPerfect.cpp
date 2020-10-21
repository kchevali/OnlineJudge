#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        int sum = 1;
        for (int i = (int)sqrt(n) + 1; i-- > 2;)
            if (n % i == 0)
                sum += (i == n / i ? i : i + n / i);
        cout << n << (n == sum ? " perfect" : abs(sum - n) <= 2 ? " almost perfect" : " not perfect") << endl;
    }
    return 0;
}