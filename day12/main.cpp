#include <bits/stdc++.h>
using namespace std;

map<string, int> vis;
long long cnt = 0;
bool free_pass_used = false;

bool is_small_cave(string s) { return s != "start" && s != "end" && s[0] >= 'a' && s[0] <= 'z'; }

bool is_big_cave(string s) { return s != "start" && s != "end" && s[0] >= 'A' && s[0] <= 'Z'; }

void util(map<string, vector<string>>& gph, string pos) {
    // if this is ending position, increase the count and return
    if (pos == "end") {
        cnt++;
        return;
    }

    for (auto x : gph[pos]) {
        if (x == "end" || (is_small_cave(x) && vis[x] == 0) || (is_small_cave(x) && vis[x] == 1 && !free_pass_used) || is_big_cave(x)) {
            
            // this_iter indicates that free_pass_used was set in this iteration of the for loop, so that it can be unset properly
            bool this_iter = false;
            if (x[0] >= 'a' && x[0] <= 'z' && vis[x] == 1 && !free_pass_used) {
                this_iter = true;
                free_pass_used = true;  // setting free_pass_used so that we don't return to a small cave once again in this path
            }

            // moving forward in the path, adding next cave and recurring on that cave
            vis[x]++;
            util(gph, x);

            // backtracking
            vis[x]--;
            // if free_pass_used was set in this iteration, unset it
            if (this_iter) free_pass_used = false;
        }
    }
    return;
}

int main(int argc, char** argv) {
    const int L = (argv[1][0] == 'b' ? 23 : 7);

    map<string, vector<string>> gph;

    for (int i = 0; i < L; i++) {
        string str;
        cin >> str;

        int ix = str.find('-');
        string a = str.substr(0, ix);
        string b = str.substr(ix + 1);

        gph[a].push_back(b);
        gph[b].push_back(a);
    }

    queue<string> qu;
    vis["start"] = 1;
    util(gph, "start");

    cout << cnt;
    return 0;
}