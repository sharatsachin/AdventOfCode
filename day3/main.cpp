#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    const int L = (argv[1][0] == 'b' ? 12 : 5);

    string x;
    vector<bitset<12>> oxy;
    while (cin >> x) oxy.push_back(bitset<12>(x));
    vector<bitset<12>> car(oxy);

    // counts elements of vector with 0 and 1 at position i
    auto counts = [](vector<bitset<12>>& v, int i) -> pair<int, int> {
        int cnt0 = 0, cnt1 = 0;
        for (auto b : v) (b[i] == 0 ? cnt0 : cnt1)++;
        return {cnt0, cnt1};
    };

    // removes elements without x at position i
    // only if it has more than one element
    auto extract = [](vector<bitset<12>>& v, int i, int x) {
        vector<bitset<12>> v2;
        for (auto b : v)
            if (b[i] == x) v2.push_back(b);
        v2.swap(v);
    };

    // PART 1
    int cnt0, cnt1;
    long long gam = 0, eps = 0;
    for (int i = 0; i < L; i++) {
        tie(cnt0, cnt1) = counts(oxy, i);
        (cnt1 > cnt0 ? gam : eps) |= (long long)(1 << i);
    }
    cout << gam * eps << '\n';

    // PART 2
    for (int i = L - 1; oxy.size() > 1; i--) {
        tie(cnt0, cnt1) = counts(oxy, i);
        extract(oxy, i, cnt1 >= cnt0);
    }
    for (int i = L - 1; car.size() > 1; i--) {
        tie(cnt0, cnt1) = counts(car, i);
        extract(car, i, cnt1 < cnt0);
    }
    cout << oxy[0].to_ulong() * car[0].to_ulong() << "\n";
    return 0;
}