#include <bits/stdc++.h>
#include "../icecream.hpp"
using namespace std;

int X1, X2, Y1, Y2;

bool within_target(int x, int y) { return x >= X1 && x <= X2 && y >= Y1 && y <= Y2; }

bool crossed(int x, int y) { return x > X2 || y < Y1; }

int main(int argc, char** argv) {
    X1 = (argv[1][0] == 'b' ? 195 : 20);
    X2 = (argv[1][0] == 'b' ? 238 : 30);
    Y1 = (argv[1][0] == 'b' ? -93 : -10);
    Y2 = (argv[1][0] == 'b' ? -67 : -5);

    // variables to store max height reached and counts
    int mmy = -1e9;
    int cnt = 0;
    
    // checking over a feasible range of starting velocities
    for (int fx = 1; fx <= 238; fx++) {
        for (int fy = -93; fy <= 100; fy++) {

            // simulating that launch
            int vx = fx, vy = fy;
            int x = 0, y = 0;
            int my = -1e9;

            // keep going until you pass the extreme coordinates of the target
            while (!crossed(x, y)) {
                x += vx, y += vy;
                my = max(my, y);
                vx--, vy--;
                if (vx < 0) vx = 0;

                // if you are within the target area
                if (within_target(x, y)) {

                    // increment counter and update max height reached
                    cnt++;
                    mmy = max(my, mmy);
                    break;
                }
            }
        }
    }

    cout << "MAX : " << mmy << '\n';
    cout << "COUNT : " << cnt;
    return 0;
}