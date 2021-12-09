#include <bits/stdc++.h>
using namespace std;

int cost(int x, vector<int>& v) {
    long long dist = 0;
    for (int el : v) {
        int k = abs(el - x);
        dist += k;
    }
    return dist;
}

int main(int argc, char** argv) {
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

    int mn = *min_element(begin(v), end(v));
    int mx = *max_element(begin(v), end(v));

    long long distm = 1e18;
    for (int x = mn; x <= mx; x++) {
        
        // cout << dist << ' ';
        distm = min(distm, dist);
    }
    cout << distm << '\n';
    return 0;
}