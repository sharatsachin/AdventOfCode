#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

int main(int argc, char** argv) {
    // no of boards
    const int P = (argv[1][0] == 'b' ? 100 : 3);

    // getting input
    string str;
    cin >> str;
    vector<int> v;
    stringstream ss(str);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(stoi(substr));
    }

    // vector to store sum of elements on each board
    vi board_sum(P, 0);
    // for each of the boards, create a seperate mapping
    // mapping from each element to its row and column number
    vector<map<int, pair<int, int>>> vmp(P);
    for (int i = 0; i < P; i++) {
        int a;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                cin >> a;
                board_sum[i] += a;
                vmp[i][a] = {j, k};
            }
        }
    }

    // int 3D matrix (P x 2 x 5) (for each row and column of each board)
    // this denotes the sum of each row and column for all the boards
    vvvi cnt_per_rc(P, vvi(2, vi(5, 0)));
    // vector to denote if a board has bingo'ed or not :P
    vi finished(P, 0);
    // number of boards which have bingo'ed
    int sumf = 0;

    // iterate over stream of called numbers
    for (auto el : v) {
        // iterate over all boards, skipping bingo'ed boards
        for (int i = 0; i < P; i++) {
            if (finished[i] == 1) continue;

            // if that board has that number
            if (vmp[i].count(el)) {
                // update count for row and column
                cnt_per_rc[i][0][vmp[i][el].first]++;
                cnt_per_rc[i][1][vmp[i][el].second]++;
                // subtract marked element from sum
                board_sum[i] -= el;

                // if after updation, a row or column is filled
                if (cnt_per_rc[i][0][vmp[i][el].first] == 5 ||
                    cnt_per_rc[i][1][vmp[i][el].second] == 5) {
                    // set that board as bingo'ed
                    finished[i] = 1;
                    // update count of bingo'ed boards, and print if first or last board
                    sumf++;
                    if (sumf == 1 || sumf == P) {
                        cout << sumf << " : " << el * board_sum[i] << '\n';
                        if (sumf == P) return 0;
                    }
                }
            }
        }
    }
    return 0;
}