#include <bits/stdc++.h>
#include "../icecream.hpp"

using namespace std;

int L;

map<vector<string>, int> dd;

int heuristic(vector<string>& vv);

struct cmp {
    bool operator()(vector<string> a, vector<string> b) {
        // return make_pair(dd[a] + heuristic(a), a) < make_pair(dd[b] + heuristic(b), b);
        return make_pair(dd[a], a) < make_pair(dd[b], b);
    }
};

bool is_room(int x) { return (x == 2 || x == 4 || x == 6 || x == 8); }

bool is_move_valid(vector<string>& vv, int x, int y) {
    if (vv[x].empty()) return false;
    char c = vv[x].back();
    // corridor to corridor
    if (!is_room(x) && !is_room(y)) return false;
    // y is a room, but not the correct room
    if (is_room(y) && c != ('A' + y / 2 - 1)) return false;
    // x is the correct room, and we are trying to leave it
    if (is_room(x) && all_of(vv[x].begin(), vv[x].end(), [x](char c) { return c == ('A' + x / 2 - 1); })) return false;

    if (is_room(y) && vv[y].size() >= L) return false;

    if (y > x) {
        for (int i = x + 1; i <= y; i++)
            if (!is_room(i) && vv[i].size()) return false;
    } else {
        for (int i = x - 1; i >= y; i--)
            if (!is_room(i) && vv[i].size()) return false;
    }
    return true;
}

int cost(vector<string>& vv, int x, int y, bool disp) {
    int cost = 0;
    if (is_room(x)) cost += (L + 1 - vv[x].size());
    cost += abs(x - y);
    if (is_room(y)) cost += (L - vv[y].size());
    int c = vv[x].back() - 'A';
    cost *= pow(10, c);
    return cost;
}

pair<int, int> direct_move(vector<string>& vv) {
    for (char c = 'D'; c >= 'A'; c--) {
        for (int i = 0; i < 11; i++) {
            int j = (c - 'A' + 1) * 2;
            if (vv[i].empty()) continue;
            if (vv[i].back() == c && all_of(vv[j].begin(), vv[j].end(), [c](char p) { return p == c; })) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int heuristic(vector<string>& vv) {
    int ret = 0;
    // IC(vv);
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < vv[i].size(); j++) {
            if (is_room(i) &&
                all_of(vv[i].begin(), vv[i].begin() + j + 1, [i](char c) { return c == ('A' + i / 2 - 1); }))
                continue;
            char c = vv[i][j];
            int k = (c - 'A' + 1) * 2;
            int cost = 0;
            if (is_room(i)) cost += (L - j);
            cost += abs(i - k);
            cost += 1;
            cost *= pow(10, c - 'A');
            // IC(i, k, cost);
            ret += cost;
        }
    }
    return ret;
}

int main(int argc, char** argv) {
    // vector<string> vv = {"", "", "BC", "", "AD", "", "BD", "", "CA", "", ""};
    // vector<string> fin = {"", "", "AA", "", "BB", "", "CC", "", "DD", "", ""};

    vector<string> vv = {"", "", "BDDC", "", "ABCD", "", "BABD", "", "CCAA", "", ""};
    vector<string> fin = {"", "", "AAAA", "", "BBBB", "", "CCCC", "", "DDDD", "", ""};

    L = vv[2].length();

    // IC(heuristic(vv));
    // IC(heuristic(fin));

    set<vector<string>, cmp> q;
    dd[vv] = 0;
    q.insert(vv);

    IC(vv);

    int k = 0;

    while (q.size()) {
        auto u = *q.begin();

        if (u == fin) break;

        k++;
        if (k % 10000 == 0) IC(k, q.size(), dd.size(), u, dd[u]);

        q.erase(q.begin());

        auto [ii, jj] = direct_move(vv);

        if (ii != -1) {
            vector<string> v(u);
            int w = cost(v, ii, jj, true);

            v[jj].push_back(v[ii].back());
            v[ii].pop_back();

            if (!dd[v]) {
                dd[v] = 1e9;
            }

            int alt = dd[u] + w;
            if (alt < dd[v]) {
                q.erase(v);
                dd[v] = alt;
                q.insert(v);
            }
        } else {
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 11; j++) {
                    if (i == j) continue;

                    vector<string> v(u);
                    if (!is_move_valid(v, i, j)) continue;
                    int w = cost(v, i, j, k == 1000);
                    if (k == 1000) IC(w);

                    v[j].push_back(v[i].back());
                    v[i].pop_back();

                    if (!dd[v]) {
                        dd[v] = 1e9;
                    }

                    int alt = dd[u] + w;
                    if (alt < dd[v]) {
                        q.erase(v);
                        dd[v] = alt;
                        q.insert(v);
                    }
                    // if (k == 1000) IC(v, dd[v]);
                }
            }
        }
    }

    IC(fin, dd[fin]);
    return 0;
}