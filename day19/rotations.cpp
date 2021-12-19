#include <bits/stdc++.h>
#include "../icecream.hpp"

#define PI 3.14159265

using namespace std;
using vvi = vector<vector<int>>;

vector<vvi> trans = {
    {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},    {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}},   {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},
    {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}},   {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},    {{1, 0, 0}, {0, 1, 0}, {0, 0, -1}},
    {{1, 0, 0}, {0, 0, -1}, {0, 1, 0}},   {{-1, 0, 0}, {0, 0, -1}, {0, 1, 0}},  {{0, 0, 1}, {0, 1, 0}, {-1, 0, 0}},
    {{0, 0, 1}, {0, -1, 0}, {-1, 0, 0}},  {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}},   {{0, -1, 0}, {1, 0, 0}, {0, 0, -1}},
    {{1, 0, 0}, {0, -1, 0}, {0, 0, -1}},  {{-1, 0, 0}, {0, -1, 0}, {0, 0, -1}}, {{-1, 0, 0}, {0, 1, 0}, {0, 0, -1}},
    {{-1, 0, 0}, {0, -1, 0}, {0, 0, -1}}, {{-1, 0, 0}, {0, -1, 0}, {0, 0, 1}},  {{-1, 0, 0}, {0, -1, 0}, {0, 0, -1}},
    {{1, 0, 0}, {0, 0, 1}, {0, -1, 0}},   {{-1, 0, 0}, {0, 0, 1}, {0, -1, 0}},  {{0, 0, -1}, {0, 1, 0}, {1, 0, 0}},
    {{0, 0, -1}, {0, -1, 0}, {1, 0, 0}},  {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}},   {{0, 1, 0}, {-1, 0, 0}, {0, 0, -1}}};

int L, M;

vvi multiply(vvi& A, vvi& B) {
    int ar = A.size(), ac = A[0].size();
    int br = B.size(), bc = B[0].size();

    vvi P(ar, vector<int>(bc, 0));

    assert(ac == br);

    for (int r = 0; r < ar; r++) {
        for (int c = 0; c < bc; c++) {
            for (int k = 0; k < ac; k++) {
                P[r][c] += A[r][k] * B[k][c];
            }
        }
    }
    // IC(P);
    return P;
}

vvi subtract(vvi& A, vvi& B) {
    int ar = A.size(), ac = A[0].size();
    int br = B.size(), bc = B[0].size();

    vvi S(ar, vector<int>(ac, 0));

    for (int r = 0; r < ar; r++) {
        for (int c = 0; c < bc; c++) {
            S[r][c] = A[r][c] - B[r][c];
        }
    }
    // IC(S);
    return S;
}

int main(int argc, char** argv) {
    // L = (argv[1][0] == 'b' ? 28 : 5);
    // M = (argv[1][0] == 'b' ? 28 : 25);

    vector<vvi> sol(24, vvi(3, vector<int>(3, 0)));

    for(int k = 0; k < 24; k++) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cin >> sol[k][i][j];
            }
        }
    }
IC(sol);
    return 0;
}