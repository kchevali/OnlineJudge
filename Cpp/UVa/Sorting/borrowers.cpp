#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

int main()
{
    string line;
    getline(cin, line);

    vector<pair<string, string>> v;
    unordered_map<string, pair<string, bool>> info;
    while (line != "END")
    {

        int n = 1;
        char ch = line[n];
        string title = "";

        while (ch != '"')
        {
            title += ch;
            ch = line[++n];
        }
        n += 5;

        string author = "";
        int len = line.length() - n;
        if (len > 0)
            author = line.substr(n, len);
        v.push_back(make_pair(author, title));
        info[title] = make_pair(author, false);

        getline(cin, line);
    }
    sort(v.begin(), v.end());
    int len = v.size();

    priority_queue<pair<string, string>, vector<pair<string, string>>, greater<pair<string, string>>> ret;
    getline(cin, line);
    while (line != "END")
    {
        string title;
        switch (line[0])
        {
        case 'R':
            title = line.substr(8, line.length() - 9);
            ret.push(make_pair(info[title].first, title));
            break;
        case 'B':
            title = line.substr(8, line.length() - 9);
            info[title].second = true;
            break;
        default:
            while (!ret.empty())
            {
                title = ret.top().second;
                ret.pop();
                info[title].second = false;
                int prev = -1;

                for (int i = 0; i < len; i++)
                {
                    string x = v[i].second;
                    if (x == title)
                    {
                        if (prev == -1)
                            cout << "Put \"" << title << "\" first" << endl;
                        else
                            cout << "Put \"" << title << "\" after \"" << v[prev].second << "\"" << endl;
                    }
                    else if (!info[x].second)
                    {
                        prev = i;
                    }
                }
            }
            cout << "END" << endl;
        }

        getline(cin, line);
    }

    return 0;
}

/*



*/
