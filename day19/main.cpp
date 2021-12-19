#include <bits/stdc++.h>
#include "../icecream.hpp"

#define PI 3.14159265

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

// list of coordinate transformation vectors
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

vi multiply(vi& A, vvi& B) {
    // find coordinates of position under new coordinate system
    vi P(3, 0);
    for (int c = 0; c < 3; c++)
        for (int k = 0; k < 3; k++) P[c] += A[k] * B[k][c];
    return P;
}

vi subtract(vi& A, vi& B) {
    vi S(3);
    for (int c = 0; c < 3; c++) S[c] = A[c] - B[c];
    return S;
}

vi add(vi& A, vi& B) {
    vi S(3);
    for (int c = 0; c < 3; c++) S[c] = A[c] + B[c];
    return S;
}

int main(int argc, char** argv) {
    L = (argv[1][0] == 'b' ? 28 : 5);

    // list of observations for each scanner
    vector<vvi> obss(L);
    string ph;
    cin >> ph;

    // just getting the input in was tedious, hmm
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

    // creating a set of all beacons, starting with beacons under first scanner
    set<vector<int>> beacons(obss[0].begin(), obss[0].end());

    // list of unmerged scanners
    set<int> unmerged;
    for (int i = 1; i < L; i++) unmerged.insert(i);

    vvi scanners;

    // while there are still unmerged scanners
    while (unmerged.size()) {
        int to_erase = -1;

        vi scanner;
        // look through unmerged scanners to find one with 12 common beacons
        for (auto um : unmerged) {
            // testing each possible orientation
            for (int i = 0; i < 24; i++) {
                bool plus12 = false;

                // mapping distance from each beacon to beacons in composite list
                map<vector<int>, int> mp;
                for (auto row1 : obss[um]) {
                    for (auto row2 : beacons) {
                        vi Y = multiply(row1, trans[i]);
                        vi Z = subtract(row2, Y);
                        mp[Z]++;
                        if (mp[Z] >= 12) {
                            scanner = Z;
                            break;
                        }
                    }
                    if (scanner.size()) break;
                }

                // once correct orientation and scanner is found, merge its beacon list
                if (scanner.size()) {
                    for (auto row : obss[um]) {
                        vi Y = multiply(row, trans[i]);
                        vi Z = add(Y, scanner);
                        beacons.insert(Z);
                    }
                    to_erase = um;
                    IC(to_erase, scanner);
                    scanners.push_back(scanner);
                    break;
                }
            }
            if (scanner.size()) break;
        }
        // erase merged scanner index from unmerged scanners
        if (to_erase != -1) unmerged.erase(to_erase);
    }
    cout << "Total number of beacons :" << beacons.size() << "\n";

    // max Manhattan distance between scanners
    int mx = 0;
    int n = scanners.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int m = abs(scanners[i][0] - scanners[j][0]);
            m += abs(scanners[i][1] - scanners[j][1]);
            m += abs(scanners[i][2] - scanners[j][2]);
            mx = max(mx, m);
        }
    }
    cout << "Max distance between scanners :" << mx << "\n";
    return 0;
}