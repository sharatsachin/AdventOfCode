#include <bits/stdc++.h>
using namespace std;

int L;
int M;

int main(int argc, char** argv) {
    L = (argv[1][0] == 'b' ? 100 : 5);
    M = (argv[1][0] == 'b' ? 100 : 10);

    vector<pair<int, int>> lows;
    vector<vector<int>> inp(L + 2,
                            vector<int>(M + 2, 9));  // sentinel values of 9s all around the input

    // direction offsets
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    long long cnt = 0;

    // getting inputs
    string str;
    for (int i = 1; i <= L; i++) {
        cin >> str;
        for (int j = 1; j <= M; j++) {
            inp[i][j] = str[j - 1] - '0';
        }
    }

    M = inp[0].size();
    // for all the different coordinates
    for (int i = 1; i <= L; i++) {
        for (int j = 1; j <= M; j++) {
            // check if 4 neighbouring points are higher
            bool is_low = true;
            for (int k = 0; k < 4; k++) is_low = is_low && inp[i][j] < inp[i + dx[k]][j + dy[k]];

            // if low, add to list and add to count
            if (is_low) {
                lows.push_back({i, j});
                cnt += (inp[i][j] + 1);
            }
        }
    }
    cout << "Sum of risk: " << cnt << '\n';

    // iterating over each low point and calculating the size of its basin
    vector<long long> sizes;
    for (auto [i, j] : lows) {
        vector<vector<bool>> vis(L + 2, vector<bool>(M + 2, false));
        queue<pair<int, int>> qu;

        // Apply BFS starting from each low point
        int sz = 0;
        vis[i][j] = 1;
        qu.push({i, j});

        while (!qu.empty()) {
            auto [x, y] = qu.front();
            sz++;
            qu.pop();
            for (int k = 0; k < 4; k++) {
                if (inp[x + dx[k]][y + dy[k]] != 9  // if neighbour is not 9
                    && !vis[x + dx[k]][y + dy[k]]   // if neighbour has not been visited
                    && inp[x][y] < inp[x + dx[k]][y + dy[k]]) {  // if neighbour is higher

                    // add neighbour to queue and mark it as visited
                    vis[x + dx[k]][y + dy[k]] = true;
                    qu.push({x + dx[k], y + dy[k]});
                }
            }
        }
        sizes.push_back(sz);
    }
    sort(rbegin(sizes), rend(sizes));

    cout << "Product of sizes of 3 largest basins : " << sizes[0] * sizes[1] * sizes[2] << '\n';
    return 0;
}