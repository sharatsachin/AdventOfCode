#include <bits/stdc++.h>
#include "../icecream.hpp"

using namespace std;

long long L;

// 39494195799979

int main(int argc, char** argv) {
    // vector<long long> W = {3, 9, 4, 9, 4, 1, 9, 5, 7, 9, 9, 9, 7, 9};
    vector<long long> W = {1, 3, 1, 6, 1, 1, 5, 1, 1, 3, 9, 6, 1, 7};

    vector<vector<long long>> p = {{1, 13, 6}, {1, 15, 7},   {1, 15, 10},  {1, 11, 2}, {26, -7, 15},
                                   {1, 10, 8}, {1, 10, 1},   {26, -5, 10}, {1, 15, 5}, {26, -3, 3},
                                   {26, 0, 5}, {26, -5, 11}, {26, -9, 12}, {26, 0, 10}};

    vector<string> WC = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n"};
    long long x, y, z;

    x = y = z = 0;
    for (long long i = 0; i < 14; i++) {
        long long w = W[i];
        x = (z % 26) + p[i][1];
        z /= p[i][0];
        x = (x != w);
        z *= (25 * x) + 1;
        z += (w + p[i][2]) * x;
        IC(w, x, y, z);
    }
    cout << '\n';

    // Simplification 1
    // x = y = z = 0;
    // for (long long i = 0; i < 14; i++) {
    //     long long A = p[i][0], B = p[i][1], C = p[i][2];
    //     long long w = W[i];

    //     x = (((z % 26) + B) != w);

    //     if (B > 0) {
    //         z = z * ((25 * x) + 1) + (w + C) * x;
    //     } else {
    //         z /= 26;
    //         z = z * ((25 * x) + 1) + (w + C) * x;
    //     }

    //     IC(w, x, y, z);
    // }
    // cout << '\n';

    // Simplification 2
    // x = y = z = 0;
    // for (long long i = 0; i < 14; i++) {
    //     long long B = p[i][1], C = p[i][2];
    //     long long w = W[i];

    //     x = (((z % 26) + B) != w);

    //     if (B > 0) {
    //         if (x == 0) { // CANNOT HAPPEN, B > 9 when B > 0
    //             z = z;
    //         } else {
    //             z = z * 26 + (w + C);
    //         }
    //     } else {
    //         if (x == 0) {
    //             z /= 26;
    //         } else {
    //             z = ((z / 26) * 26) + (w + C);
    //         }
    //     }
    //     IC(w, x, y, z);
    // }
    // cout << '\n';

    // Simplification 3
    // x = y = z = 0;
    // for (long long i = 0; i < 14; i++) {
    //     long long B = p[i][1], C = p[i][2];
    //     long long w = W[i];

    //     x = (((z % 26) + B) != w);

    //     if (B > 0) {
    //         z = z * 26 + (w + C);
    //     } else {
    //         if (x == 0) {
    //             z /= 26;
    //         } else {
    //             z = ((z / 26) * 26) + (w + C);
    //         }
    //     }
    //     IC(w, x, y, z);
    // }
    // cout << '\n';

    // final pop with condition, that makes it clear
    x = y = z = 0;
    vector<long long> Z;
    for (long long i = 0; i < 14; i++) {
        long long B = p[i][1], C = p[i][2];
        long long w = W[i];

        if (B > 0) {
            Z.push_back(w + C);
        } else {
            x = ((Z.back() + B) != w);
            if (x == 0) {
                Z.pop_back();
            } else {
                Z.pop_back();
                Z.push_back(w + C);
            }
        }
        IC(w, x, y, Z);
    }
    cout << '\n';

    x = y = z = 0;
    Z.clear();
    // Just for help doing the calculations by hand
    for (long long i = 0; i < 14; i++) {
        long long B = p[i][1], C = p[i][2];
        string w = WC[i];

        if (B > 0) {
            IC(w, C);
        } else {
            IC('P', B, w);
        }
    }
    cout << '\n';

    return 0;
}