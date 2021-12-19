#include <bits/stdc++.h>
#include "../icecream.hpp"

#define PI 3.14159265

using namespace std;
using vvi = vector<vector<int>>;

vector<vvi> trans = {
    {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},    {{1, 0, 0}, {0, 0, -1}, {0, 1, 0}},  {{1, 0, 0}, {0, -1, 0}, {0, 0, -1}},
    {{1, 0, 0}, {0, 0, 1}, {0, -1, 0}},   {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}},  {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}},
    {{0, 1, 0}, {1, 0, 0}, {0, 0, -1}},   {{0, 0, -1}, {1, 0, 0}, {0, -1, 0}}, {{-1, 0, 0}, {0, -1, 0}, {0, 0, 1}},
    {{-1, 0, 0}, {0, 0, -1}, {0, -1, 0}}, {{-1, 0, 0}, {0, 1, 0}, {0, 0, -1}}, {{-1, 0, 0}, {0, 0, 1}, {0, 1, 0}},
    {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}},   {{0, 0, 1}, {-1, 0, 0}, {0, -1, 0}}, {{0, -1, 0}, {-1, 0, 0}, {0, 0, -1}},
    {{0, 0, -1}, {-1, 0, 0}, {0, 1, 0}},  {{0, 0, -1}, {0, 1, 0}, {1, 0, 0}},  {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}},
    {{0, 0, 1}, {0, -1, 0}, {1, 0, 0}},   {{0, -1, 0}, {0, 0, -1}, {1, 0, 0}}, {{0, 0, -1}, {0, -1, 0}, {-1, 0, 0}},
    {{0, -1, 0}, {0, 0, 1}, {-1, 0, 0}},  {{0, 0, 1}, {0, 1, 0}, {-1, 0, 0}},  {{0, 1, 0}, {0, 0, -1}, {-1, 0, 0}}};

int L, M;

vvi multiply(vvi& A, vvi& B) {
    int ar = A.size(), ac = A[0].size();
    int bc = B[0].size();
    vvi P(ar, vector<int>(bc, 0));

    for (int r = 0; r < ar; r++)
        for (int c = 0; c < bc; c++)
            for (int k = 0; k < ac; k++) P[r][c] += A[r][k] * B[k][c];
    return P;
}

vvi subtract(vvi& A, vvi& B) {
    int ar = A.size(), ac = A[0].size();
    vvi S(ar, vector<int>(ac, 0));
    for (int r = 0; r < ar; r++)
        for (int c = 0; c < ac; c++) S[r][c] = A[r][c] - B[r][c];
    return S;
}

vvi add(vvi& A, vvi& B) {
    int ar = A.size(), ac = A[0].size();
    vvi S(ar, vector<int>(ac, 0));
    for (int r = 0; r < ar; r++)
        for (int c = 0; c < ac; c++) S[r][c] = A[r][c] + B[r][c];
    return S;
}

int main(int argc, char** argv) {
    L = (argv[1][0] == 'b' ? 28 : 5);

    vector<vvi> obss(L);
    string ph;
    cin >> ph;
    for (int tc = 0; tc < L; tc++) {
        cin >> ph;
        cin >> ph;
        cin >> ph;

        for (int l = 0;; l++) {
            string str;
            cin >> str;
            if (str == "---") break;
            vector<int> v;
            stringstream ss(str);
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                v.push_back(stoi(substr));
            }
            obss[tc].push_back(v);
        }
    }

    set<vector<int>> beacons(obss[0].begin(), obss[0].end());

    set<int> unmerged;
    for (int i = 1; i < L; i++) unmerged.insert(i);

    vvi scanners;

    while (unmerged.size()) {
        // IC(unmerged);
        // IC(beacons, beacons.size());
        int to_erase = -1;

        // vector<int> unmerged = {10, 21, 4,  2,  13, 22, 23, 6,  24, 25, 3, 7,  16, 5,
        //                         1,  19, 20, 12, 11, 14, 9,  15, 17, 18, 8, 26, 27};

        bool merged = false;
        for (auto um : unmerged) {
            // IC(um);
            for (int i = 0; i < 24; i++) {
                map<vector<int>, int> mp;
                for (auto row1 : obss[um]) {
                    for (auto row2 : beacons) {
                        vvi rr1 = {row1};
                        vvi rr2 = {row2};
                        // IC(rr1, rr2);
                        vvi Y = multiply(rr1, trans[i]);
                        vvi Z = subtract(rr2, Y);
                        // IC(rr1, rr2, trans[i], Y, Z);
                        mp[Z[0]]++;
                    }
                }
                for (auto [x, y] : mp) {
                    if (y >= 12) {
                        // IC(um, trans[i], x, y);

                        for (auto row : obss[um]) {
                            vvi rr = {row};
                            vvi Y = multiply(rr, trans[i]);
                            vvi X = {x};
                            vvi Z = add(Y, X);
                            beacons.insert(Z[0]);
                            // IC(row, Y, X, Z[0]);
                        }
                        to_erase = um;
                        IC(to_erase, x);
                        scanners.push_back(x);
                        merged = true;
                        break;
                    }
                }
                if (merged == true) break;
            }
            if (merged == true) break;
        }
        if (to_erase != -1) unmerged.erase(to_erase);
    }

    IC(beacons, beacons.size());
    IC(scanners);

    int mx = 0;
    int n = scanners.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int m = 0;
            m += abs(scanners[i][0] - scanners[j][0]);
            m += abs(scanners[i][1] - scanners[j][1]);
            m += abs(scanners[i][2] - scanners[j][2]);
            mx = max(mx, m);
        }
    }
    IC(mx);

    return 0;
}