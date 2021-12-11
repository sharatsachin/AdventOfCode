#include <bits/stdc++.h>
using namespace std;

int L;
int M;

int main(int argc, char** argv) {
    L = (argv[1][0] == 'b' ? 10 : 10);
    M = (argv[1][0] == 'b' ? 10 : 10);

    vector<vector<int>> inp(L + 2,
                            vector<int>(M + 2, 11));  // sentinel values of 11s all around the input

    // direction offsets
    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, 1, -1, -1, 1, -1, 1};

    // getting inputs
    string str;
    for (int i = 1; i <= L; i++) {
        cin >> str;
        for (int j = 1; j <= M; j++) inp[i][j] = str[j - 1] - '0';
    }

    int tot_flash = 0;

    for (int st = 0;; st++) {
        int st_flash = 0;

        // find all the points that are going to flash and add them to `highs`
        vector<pair<int, int>> highs;
        for (int i = 1; i <= L; i++) {
            for (int j = 1; j <= M; j++) {
                inp[i][j]++;  // incrementing each octopus
                if (inp[i][j] == 10) highs.push_back({i, j});
            }
        }

        // visited matrix
        vector<vector<bool>> vis(L + 2, vector<bool>(M + 2, false));

        for (auto [i, j] : highs) {
            queue<pair<int, int>> qu;

            // Apply BFS starting from each high point
            if (vis[i][j] == 1) continue;  // skip if it has already flashed

            vis[i][j] = 1;
            qu.push({i, j});

            while (!qu.empty()) {
                auto [x, y] = qu.front();

                // processing single flash, incrementing all the neighbours
                inp[x][y] = 0;
                st_flash++;
                for (int k = 0; k < 8; k++)
                    if (inp[x + dx[k]][y + dy[k]] != 0) inp[x + dx[k]][y + dy[k]]++;
                qu.pop();

                // check if any of the octopuses are about to flash
                for (int k = 0; k < 8; k++) {
                    if (inp[x + dx[k]][y + dy[k]] == 10   // if octopus is about to flash
                        && !vis[x + dx[k]][y + dy[k]]) {  // if octopus has not yet flashed
                        // add octopus to queue and mark it as visited
                        vis[x + dx[k]][y + dy[k]] = true;
                        qu.push({x + dx[k], y + dy[k]});
                    }
                }
            }
        }

        if (st_flash == 100) {
            cout << "All octopuses flash together on step : " << st + 1 << '\n';
            break;
        }

        tot_flash += st_flash;
        if (st + 1 == 100) cout << "Flashes after 100 steps : " << tot_flash << '\n';
    }
    return 0;
}