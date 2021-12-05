#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    const int L = (argv[1][0] == 'b' ? 500 : 10);

    // 2D matrices to store number of times a point was encountered
    vector<vector<int>> mat1(1000, vector<int>(1000, 0));
    vector<vector<int>> mat2(mat1);
    int sol1 = 0, sol2 = 0;

    // function to add a point to the matrices
    // update solution if intersection is present
    auto intersect = [&mat1, &mat2, &sol1, &sol2](int x, int y, bool vh) {
        if (vh) {  // if line is vertical or horizontal
            mat1[x][y]++;
            if (mat1[x][y] == 2) sol1++;
        }
        mat2[x][y]++;
        if (mat2[x][y] == 2) sol2++;
    };

    int a, b, c, d;
    for (int i = 0; i < L; i++) {
        scanf("%d,%d -> %d,%d", &a, &b, &c, &d);

        // arrange such that a <= c and (b <= d if a == c)
        if (a > c) swap(a, c), swap(b, d);
        if (a == c && b > d) swap(b, d);
        int x = a, y = b;

        // check if line is vertical or horizontal
        bool vh = (a == c || b == d);

        // finding each point in the line
        if (a == c) {
            intersect(x, y, vh);
            while (y < d) {
                y++;
                intersect(x, y, vh);
            }
        } else {
            intersect(x, y, vh);
            while (x < c) {
                x += 1;
                y += ((d - b) / (c - a));
                intersect(x, y, vh);
            }
        }
    }

    // solution for both subtasks
    cout << sol1 << '\n' << sol2 << '\n';
    return 0;
}