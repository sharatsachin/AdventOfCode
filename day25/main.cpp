#include <bits/stdc++.h>
#include "../icecream.hpp"

using namespace std;

int L, M;

int run(vector<string>& vv) {
    set<pair<int, int>> move_r, move_d;

    int n_moved = 0;
    for (int j = 0; j < L; j++)
        for (int i = 0; i < M; i++)
            if (vv[j][i] == '>' && vv[j][(i + 1) % M] == '.') move_r.insert({j, i});

    for (auto& [j, i] : move_r) vv[j][(i + 1) % M] = '>', vv[j][i] = '.';

    for (int j = 0; j < L; j++)
        for (int i = 0; i < M; i++)
            if (vv[j][i] == 'v' && vv[(j + 1) % L][i] == '.') move_d.insert({j, i});

    for (auto& [j, i] : move_d) vv[(j + 1) % L][i] = 'v', vv[j][i] = '.';

    return move_r.size() + move_d.size();
}

int main(int argc, char** argv) {
    L = (argv[1][0] == 'b' ? 137 : 9);
    vector<string> vv;

    string s;
    for (int i = 0; i < L; i++) cin >> s, vv.push_back(s);

    M = s.size();

    int steps = 0;
    while (run(vv)) steps++;
    cout << steps + 1 << "\n";
    return 0;
}