#include <bits/stdc++.h>
#include "../icecream.hpp"

using namespace std;
using ll = long long;

ll L;

int main(int argc, char** argv) {
    L = (argv[1][0] == 'b' ? 420 : 60);

    vector<vector<ll>> v(L, vector<ll>(7));

    set<ll> xs, ys, zs;

    // input and creation of sets
    for (ll i = 0; i < L; i++) {
        string s;
        cin >> s;
        v[i][0] = (s == "on");
        for (ll j = 1; j < 7; j++) cin >> v[i][j];
        if (v[i][1] > v[i][2]) swap(v[i][1], v[i][2]);
        if (v[i][3] > v[i][4]) swap(v[i][3], v[i][4]);
        if (v[i][5] > v[i][6]) swap(v[i][5], v[i][6]);

        xs.insert(v[i][1]);
        xs.insert(v[i][2] + 1);
        ys.insert(v[i][3]);
        ys.insert(v[i][4] + 1);
        zs.insert(v[i][5]);
        zs.insert(v[i][6] + 1);
    }

    // doing coordinate compression
    vector<ll> xv(xs.begin(), xs.end());
    vector<ll> yv(ys.begin(), ys.end());
    vector<ll> zv(zs.begin(), zs.end());

    vector<vector<vector<bool>>> c(xs.size(), vector<vector<bool>>(ys.size(), vector<bool>(zs.size())));

    // to find starting and ending index for range of values
    auto ix = [](vector<ll>& v, ll a, ll b) {
        ll aix = lower_bound(v.begin(), v.end(), a) - v.begin();
        ll bix = lower_bound(v.begin(), v.end(), b) - v.begin();
        return pair(aix, bix);
    };

    // find number of elements compressed into a single cell
    auto size = [&xv, &yv, &zv](ll xi, ll yi, ll zi) {
        return (xv[xi + 1] - xv[xi]) * (yv[yi + 1] - yv[yi]) * (zv[zi + 1] - zv[zi]);
    };

    // performing on and off in a 3D range
    for (ll i = 0; i < L; i++) {
        auto [xis, xie] = ix(xv, v[i][1], v[i][2] + 1);
        auto [yis, yie] = ix(yv, v[i][3], v[i][4] + 1);
        auto [zis, zie] = ix(zv, v[i][5], v[i][6] + 1);

        for (ll xi = xis; xi != xie; xi++)
            for (ll yi = yis; yi != yie; yi++)
                for (ll zi = zis; zi != zie; zi++) c[xi][yi][zi] = v[i][0];
    }

    // finding total sum
    long long sum = 0;
    for (ll xi = 0; xi != xv.size(); xi++)
        for (ll yi = 0; yi != yv.size(); yi++)
            for (ll zi = 0; zi != zv.size(); zi++)
                if (c[xi][yi][zi]) sum += size(xi, yi, zi);

    IC(sum);
    return 0;
}