#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    const long long L = (argv[1][0] == 'b' ? 100 : 16);
    string str;
    cin >> str;

    map<pair<char, char>, long long> counter;
    long long l = str.length();
    for (long long i = 0; i < l - 1; i++) counter[{str[i], str[i + 1]}]++;

    map<pair<char, char>, char> mp;
    for (long long i = 0; i < L; i++) {
        string a, b, c;
        cin >> a >> b >> c;
        mp[{a[0], a[1]}] = c[0];
    }

    map<pair<char, char>, long long> temp_counter;

    for (long long tc = 0; tc < 40; tc++) {
        for (auto [cc, x] : counter) {
            long long o = counter[cc];
            char y = mp[cc];
            temp_counter[{cc.first, y}] += o;
            temp_counter[{y, cc.second}] += o;
        }
        counter.swap(temp_counter);
        temp_counter.clear();
    }

    map<char, long long> css;
    for (auto [cc, x] : counter) {
        css[cc.first] += x;
    }
    css[str[l - 1]] += 1;

    long long mx = 0, mn = 1e18;
    for (auto [cc, x] : css) mn = min(mn, x), mx = max(mx, x);
    cout << mx - mn << '\n';
    return 0;
}