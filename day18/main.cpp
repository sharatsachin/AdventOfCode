#include <bits/stdc++.h>
#include "../icecream.hpp"

using namespace std;

// defining new types
using lpii = list<pair<int, int>>;
// iterator pointing to elements of the above list type
using lpiter = list<pair<int, int>>::iterator;

int L;

lpii parse(string s) {
    // to parse the input strings into lists of pair<int, int>
    // the first item in the pair represents the value
    // the second represents the level of nesting
    
    // for eg: "[[9,3],[[9,9],[6,[4,9]]]]"
    // into [(9, 2), (3, 2), (9, 3), (9, 3), (6, 3), (4, 4), (9, 4)]
    lpii snum;
    int depth = 0;
    for (char c : s) {
        if (c == ',')
            continue;
        else if (c == ']')
            depth--;
        else if (c == '[')
            depth++;
        else
            snum.push_back({c - '0', depth});
    }
    return snum;
}

pair<int, lpiter> can_explode_or_split(lpii& snum) {
    // recieving a list, it determines if there are any elements that
    // can explode or split

    lpiter it;
    // returns "1" and iterator to element that can be exploded
    for (it = snum.begin(); it != snum.end(); ++it) {
        auto [el, dep] = *it;
        if (dep >= 5) return {1, it};
    }

    // returns "2" and iterator to element that can be split
    for (it = snum.begin(); it != snum.end(); ++it) {
        auto [el, dep] = *it;
        if (el >= 10) return {2, it};
    }

    // means the list is final, no explosions or splits left
    return {0, it};
}

lpii explode(lpii& snum, lpiter it) {
    // recieving the list, and an iterator to the position to explode

    // value and depth of first element
    auto [el, dep] = *it;
    if (it != snum.begin()) {
        // if not first element, add value to previous element
        prev(it)->first += el;
    }

    // value and depth of following element
    auto [el2, dep2] = *next(it);
    if (next(it) != snum.end()) {
        // if not last element, add value to next element
        next(next(it))->first += el2;
    }

    // set first element to 0 and update level of nesting
    it->first = 0, it->second--;
    // erase following element
    snum.erase(next(it));
    return snum;
}

lpii split(lpii& snum, lpiter it) {
    // recieving the list, and an iterator to the position to split

    // value and depth of first element
    auto [el, dep] = *it;

    // insert new element in position, and update both elements
    snum.insert(it, {el / 2, dep + 1});
    it->first = (el + 1) / 2, it->second++;
    return snum;
}

lpii add(lpii& snum, lpii& snum2) {
    // add two Snailfish numbers

    if (snum2.size() != 0) {
        // performing simple appending of second list to first list
        // with updated level of nesting
        for (auto it = snum.begin(); it != snum.end(); ++it) it->second++;
        for (auto it = snum2.begin(); it != snum2.end(); ++it) it->second++;
        snum.splice(snum.end(), snum2);
    }

    // if exploding any element is possible, do that first
    // otherwise split if possible
    while (true) {
        auto [which, iter] = can_explode_or_split(snum);
        if (which == 0) break;
        // explosion is possible
        else if (which == 1)
            snum = explode(snum, iter);
        // split is possible
        else if (which == 2)
            snum = split(snum, iter);
    }
    return snum;
}

int dimension(lpii& snum) {
    // calculate dimension of Snailfish numbers
    while (snum.size() != 1) {
        // find two elements at same level of nexting, calculate dim and break
        // until only one element is left in list
        for (auto it = snum.begin(); it != snum.end(); it++) {
            auto [el, dep] = *it;
            auto [el2, dep2] = *next(it);
            if (dep == dep2) {
                it->first = 3 * el + 2 * el2, it->second--;
                snum.erase(next(it));
                break;
            }
        }
    }
    // only one element left in list, returning its value
    return snum.begin()->first;
}

int main(int argc, char** argv) {
    L = (argv[1][0] == 'b' ? 100 : 10);

    string s;
    vector<string> vs;

    cin >> s;
    vs.push_back(s);
    lpii snum1 = parse(s), snum2;

    for (int i = 1; i < L; i++) {
        cin >> s;
        vs.push_back(s);
        snum2 = parse(s);
        snum1 = add(snum1, snum2);
    }
    cout << "Dimension of sum of Snailfish numbers : " << dimension(snum1) << '\n';

    int mx = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            if (i == j) continue;
            snum1 = parse(vs[i]);
            snum2 = parse(vs[j]);
            snum1 = add(snum1, snum2);
            int dim = dimension(snum1);
            mx = max(mx, dim);
        }
    }
    cout << "Max dimension of sum of any two Snailfish numbers : " << mx << '\n';
    return 0;
}