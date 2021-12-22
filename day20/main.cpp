#include <bits/stdc++.h>
#include "../icecream.hpp"

using namespace std;

int L;

int main(int argc, char** argv) {
    L = (argv[1][0] == 'b' ? 100 : 5);

    string enh;
    cin >> enh;

    int k = 100;
    k++;

    vector<vector<int>> inp(L + 2 * k, vector<int>(L + 2 * k, 0));
    for (int i = k; i < L + k; i++) {
        string s;
        cin >> s;
        IC(s);
        for (int j = k; j < L + k; j++) inp[i][j] += (s[j - k] == '#');
    }

    // IC(inp, cnt);

    for (int i = 0; i < 50; i++) {
        // cnt = 0;
        vector<vector<int>> out(L + 2 * k, vector<int>(L + 2 * k, 0));
        for (int x = 1; x < L + 2 * k - 1; x++) {
            for (int y = 1; y < L + 2 * k - 1; y++) {
                // IC(x, y);
                int bin = inp[x - 1][y - 1] * (1 << 8);
                bin += inp[x - 1][y] * (1 << 7);
                bin += inp[x - 1][y + 1] * (1 << 6);
                bin += inp[x][y - 1] * (1 << 5);
                bin += inp[x][y] * (1 << 4);
                bin += inp[x][y + 1] * (1 << 3);
                bin += inp[x + 1][y - 1] * (1 << 2);
                bin += inp[x + 1][y] * (1 << 1);
                bin += inp[x + 1][y + 1] * (1 << 0);
                out[x][y] += (enh[bin] == '#');
                // cnt += out[x][y];
            }
        }
        inp.swap(out);
        // IC(cnt);
    }

    int cnt = 0;
    for (int x = 2; x < L + 2 * k - 2; x++) {
        for (int y = 2; y < L + 2 * k - 2; y++) {
            cout << (inp[x][y] == 1 ? '#' : '.');
            cnt += inp[x][y];
        }
        cout << '\n';
    }
    cout << cnt;

    return 0;
}