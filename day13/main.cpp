#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    const int L = (argv[1][0] == 'b' ? 799 : 18);
    const int M = (argv[1][0] == 'b' ? 12 : 2);

    set<pair<int, int>> vv;

    // get input, store each coordinate in a set
    for (int i = 0; i < L; i++) {
        string str;
        cin >> str;

        int ix = str.find(',');
        int a = stoi(str.substr(0, ix));
        int b = stoi(str.substr(ix + 1));
        vv.insert({a, b});
    }

    set<pair<int, int>> vb;

    // for each fold, iterate over all the points in the set,
    // find their location after folding and add them to a new set
    for (int i = 0; i < M; i++) {
        string str;
        cin >> str;
        cin >> str;
        cin >> str;

        int ix = str.find('=');
        char a = str[ix - 1];
        int b = stoi(str.substr(ix + 1));

        for (auto [x, y] : vv) {
            if (a == 'x')
                x = (x > b ? b - (x - b) : x);
            else
                y = (y > b ? b - (y - b) : y);
            vb.insert({x, y});
        }

        // swapping vv and vb
        vv.swap(vb);
        vb.clear();
    }

    vector<vector<char>> mat(100, vector<char>(100, ' '));
    for (auto [x, y] : vv) mat[x][y] = '#';

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 50; j++) cout << mat[j][i] << " \n"[j == 49];
    return 0;
}