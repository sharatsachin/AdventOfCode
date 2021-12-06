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

    int x1, y1, x2, y2;
    for (int i = 0; i < L; i++) {
        scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
        // check if line is vertical or horizontal
        bool vh = (x1 == x2 || y1 == y2);

        // finding each point in the line
        int n = max(abs(x1 - x2), abs(y1 - y2)) + 1;
        int dx = (x2 - x1) / (n - 1);
        int dy = (y2 - y1) / (n - 1);
        for (int x = x1, y = y1; n--; x += dx, y += dy) intersect(x, y, vh);
    }

    // solution for both subtasks
    cout << sol1 << '\n' << sol2 << '\n';
    return 0;
}