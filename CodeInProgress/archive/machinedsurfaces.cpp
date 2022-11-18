#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

struct Array
{
    string name;
    int size, d;
    vector<int> bases;
    vector<int> start;
};

int main()
{
    int tot, que;
    cin >> tot >> que;
    vector<Array> v;

    unordered_map<string, int> m;

    for (int i = 0; i < tot; i++)
    {

        Array arr = Array();
        int base;
        cin >> arr.name >> base >> arr.size >> arr.d;
        arr.bases.push_back(base);
        m[arr.name] = v.size();
        v.push_back(arr);

        for (int j = 0; j < arr.d; j++)
        {
            int a, b;
            cin >> a >> b;
            arr.start.push_back(a);
            arr.bases.push_back(base += (b - a) * arr.size);
        }
    }
    return 0;
}

/*



*/