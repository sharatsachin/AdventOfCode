#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll X, Y;

map<tuple<ll, ll, ll, ll>, pair<ll, ll>> mp;

pair<ll, ll> count_wins(ll p1, ll p2, ll s1, ll s2) {
    if (s1 >= 21) return {1, 0};
    if (s2 >= 21) return {0, 1};
    if (mp.find({p1, p2, s1, s2}) != mp.end()) return mp[{p1, p2, s1, s2}];

    pair<ll, ll> sol = {0, 0};

    for (ll i = 1; i <= 3; i++) {
        for (ll j = 1; j <= 3; j++) {
            for (ll k = 1; k <= 3; k++) {
                int n_p1 = (p1 + i + j + k) % 10;
                int n_s1 = n_p1 + s1 + 1;
                auto fut = count_wins(p2, n_p1, s2, n_s1);
                sol.first += fut.second;
                sol.second += fut.first;
            }
        }
    }

    mp[{p1, p2, s1, s2}] = sol;
    return sol;
}

int main(int argc, char** argv) {
    X = (argv[1][0] == 'b' ? 1 : 4);
    Y = (argv[1][0] == 'b' ? 3 : 8);
    auto sol = count_wins(X - 1, Y - 1, 0, 0);
    cout << max(sol.first, sol.second);
}