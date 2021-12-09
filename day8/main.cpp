#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    const int L = (argv[1][0] == 'b' ? 200 : 10);

    map<string, int> str_map = {{"abcefg", 0},  {"cf", 1},    {"acdeg", 2},  {"acdfg", 3},
                                {"bcdf", 4},    {"abdfg", 5}, {"abdefg", 6}, {"acf", 7},
                                {"abcdefg", 8}, {"abcdfg", 9}};

    long long cnt = 0;

    // for each line of input
    for (int i = 0; i < L; i++) {
        // get the input strings in that line
        vector<string> inp(15);
        for (int j = 0; j < 15; j++) cin >> inp[j];

        string orig = "abcdefg";
        string dup = orig;

        // do for all permutations of dup ("abcdefg")
        do {
            // create map between original and changed characters
            map<char, char> cc;
            for (int j = 0; j < 7; j++) cc[dup[j]] = orig[j];

            // convert all the strings into transformed strings using above map
            vector<string> mapped(15);
            transform(inp.begin(), inp.end(), mapped.begin(), [&cc](string s) {
                string t = "";
                for (char c : s) t += cc[c];
                sort(t.begin(), t.end());
                return t;
            });

            // check if all 10 signal patterns are present in str_map
            bool contains = all_of(mapped.begin(), mapped.begin() + 10,
                                   [str_map](string s) { return str_map.count(s); });

            if (contains) {
                // get that four digit output value
                cnt += (str_map[mapped[11]] * 1000 + str_map[mapped[12]] * 100 +
                        str_map[mapped[13]] * 10 + str_map[mapped[14]]);
                break;
            }
        } while (next_permutation(dup.begin(), dup.end()));
    }

    cout << cnt;
    return 0;
}