#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    const int P = (argv[1][0] == 'b' ? 100 : 3);

    string str;
    cin >> str;

    vector<int> v;
    stringstream ss(str);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(stoi(substr));
    }

    vector<map<int, pair<int, int>>> vmp(P);

    for (int i = 0; i < P; i++) {
        int a;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                cin >> a;
                vmp[i][a] = {j, k};
            }
        }
    }

    vector<vector<vector<int>>> marked(P, vector<vector<int>>(2, vector<int>(5, 0)));
    vector<vector<vector<int>>> done(P, vector<vector<int>>(5, vector<int>(5, 0)));
    vector<int> finished(P, 0);

    int winner = -1;
    for (auto el : v) {
        for (int i = 0; i < P; i++) {
            if (finished[i] == 1) continue;

            if (vmp[i].count(el)) {
                marked[i][0][vmp[i][el].first]++;
                marked[i][1][vmp[i][el].second]++;
                done[i][vmp[i][el].first][vmp[i][el].second] = 1;

                if (marked[i][0][vmp[i][el].first] == 5 || marked[i][1][vmp[i][el].second] == 5) {
                    finished[i] = 1;
                    int sumf = accumulate(finished.begin(), finished.end(), 0);

                    int sum = 0;
                    for (auto [x, y] : vmp[i]) {
                        if (done[i][y.first][y.second] == 0) sum += x;
                    }
                    if (sumf == 1 || sumf == P) {
                        cout << "Position " << sumf << " has points " << el * sum << '\n';
                        if (sumf == 100) return 0;
                    }
                }
            }
        }
    }
    return 0;
}