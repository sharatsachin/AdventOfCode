#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, int> dd, pp, etc;
struct cmp {
    bool operator()(pair<int, int> a, pair<int, int> b) const { 
        return make_pair(dd[a], a) < make_pair(dd[b], b); 
    }
};

int main(int argc, char** argv) {
    int L = (argv[1][0] == 'b' ? 100 : 10);

    vector<vector<int>> inp(L * 5, vector<int>(L * 5));

    // direction offsets
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    // getting inputs
    string str;
    for (int i = 0; i < L; i++) {
        cin >> str;
        for (int j = 0; j < L; j++) inp[i][j] = str[j] - '0';
    }

    // creating input matrix obtained by repeating 5 times vertically and horizontally
    for (int i = 0; i < L * 5; i++) {
        for (int j = 0; j < L * 5; j++) {
            if (i >= L || j >= L) {
                if (i >= L)
                    inp[i][j] = (inp[i - L][j]) % 9 + 1;
                else
                    inp[i][j] = (inp[i][j - L]) % 9 + 1;
            }
        }
    }
    L = L * 5;

    // seeding distances with ~infinity
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) dd[{i, j}] = 1e9;
    }

    // standard Dijkstra with priority queue
    set<pair<int, int>, cmp> q;
    dd[{0, 0}] = 0;
    q.insert({0, 0});

    while (q.size()) {
        auto [x, y] = *q.begin();
        q.erase(q.begin());

        for (int i = 0; i < 4; i++) {
            int x_ = x + dx[i];
            int y_ = y + dy[i];
            if (x_ < 0 || x_ >= L || y_ < 0 || y_ >= L) continue;

            int alt = dd[{x, y}] + inp[x_][y_];

            if (alt < dd[{x_, y_}]) {
                q.erase({x_, y_});
                dd[{x_, y_}] = alt;
                q.insert({x_, y_});
            }
        }
    }
    cout << dd[{L - 1, L - 1}];

    return 0;
}