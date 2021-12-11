#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    const int L = (argv[1][0] == 'b' ? 102 : 10);

    long long cnt = 0;
    map<char, int> error_scores = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    map<char, int> c2o = {{')', '('}, {']', '['}, {'}', '{'}, {'>', '<'}};
    map<char, int> o2c = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    map<char, int> completion_scores = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

    string str;
    vector<long long> scores;

    for (int i = 0; i < L; i++) {
        int cost = 0;
        long long score = 0;
        cin >> str;
        stack<char> st;

        for (auto c : str) {
            if (c == '(' || c == '[' || c == '{' || c == '<') {
                st.push(c);
            } else {
                char x = st.top();
                if (x != c2o[c]) {
                    cost += error_scores[c];
                    while (!st.empty()) st.pop();
                    break;
                }
                st.pop();
            }
        }

        while (st.size()) {
            char y = st.top();
            st.pop();
            score = score * 5 + completion_scores[o2c[y]];
        }

        if (score) scores.push_back(score);
        cnt += cost;
    }

    cout << cnt << '\n';
    sort(scores.begin(), scores.end());
    cout << scores[scores.size() / 2];
    return 0;
}