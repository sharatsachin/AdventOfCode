#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    const int days = (argv[1][0] == 'b' ? 256 : 80);

    vector<long long> dp(6, 0);

    // precomputing number of laterns after specified days for [1,5]
    for (int x = 1; x < 6; x++) {
        vector<long long> mp(10, 0);
        mp[x] = 1;

        int curd = 0;
        // for every day
        while (curd < days) {
            // decremnent all the numbers by one
            int ze = mp[0];
            for (int i = 0; i < 9; i++) mp[i] = mp[i + 1];
            // remove old zeros and replaces with equal number of sixes and eights
            mp[6] += ze, mp[8] += ze;
            // increment current day counter
            curd++;
        }
        // solution for x = sum of number of all laterns at different stages
        dp[x] = accumulate(mp.begin(), mp.end(), 0ll);
    }

    // getting input and storing array in vector v
    string str;
    cin >> str;
    vector<int> v;
    stringstream ss(str);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(stoi(substr));
    }

    // adding up precomputed number of laterns after specified days
    long long sol = 0;
    for (auto x : v) {
        sol += dp[x];
    }
    cout << sol << "\n";
    return 0;
}