#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    const int days = (argv[1][0] == 'b' ? 256 : 80);

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

    // starting number of fishes
    vector<long long> mp(10, 0);
    for (auto el : v) mp[el]++;

    int curd = 0;
    // for every day
    while (curd < days) {
        // decremnent all the numbers by one
        long long ze = mp[0];
        for (int i = 0; i < 9; i++) mp[i] = mp[i + 1];
        // remove old zeros and replaces with equal number of sixes and eights
        mp[6] += ze, mp[8] += ze;
        // increment current day counter
        curd++;
        cout << curd << ' ' << accumulate(mp.begin(), mp.end(), 0ll) << '\n';
    }
    cout << accumulate(mp.begin(), mp.end(), 0ll) << "\n";
    return 0;
}