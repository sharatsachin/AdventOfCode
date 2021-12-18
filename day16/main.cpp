#include <bits/stdc++.h>
using namespace std;

string HexToBin(string hexdec) {
    // convert hex string to binary string, easiest way in C++ lol 
    long long i = 0;
    string ret;
    for (char c : hexdec) {
        switch (c) {
            case '0':
                ret += "0000";
                break;
            case '1':
                ret += "0001";
                break;
            case '2':
                ret += "0010";
                break;
            case '3':
                ret += "0011";
                break;
            case '4':
                ret += "0100";
                break;
            case '5':
                ret += "0101";
                break;
            case '6':
                ret += "0110";
                break;
            case '7':
                ret += "0111";
                break;
            case '8':
                ret += "1000";
                break;
            case '9':
                ret += "1001";
                break;
            case 'A':
                ret += "1010";
                break;
            case 'B':
                ret += "1011";
                break;
            case 'C':
                ret += "1100";
                break;
            case 'D':
                ret += "1101";
                break;
            case 'E':
                ret += "1110";
                break;
            case 'F':
                ret += "1111";
                break;
        }
    }
    return ret;
}

long long sumver = 0;

// resursive parser, extract sections from the string, part by part
pair<string, long long> parse(string data) {
    if (data.length() == 0) return {"", 0};

    long long vers = stoll(data.substr(0, 3), 0, 2);
    sumver += vers;
    data = data.substr(3);

    long long tid = stoll(data.substr(0, 3), 0, 2);
    data = data.substr(3);

    if (tid == 4) {
        string t = "";
        while (1) {
            t += data.substr(1, 4);
            long long x = data[0] - '0';
            data = data.substr(5);
            if (x == 0) break;
        }
        return {data, stoll(t, 0, 2)};
    } else {
        long long ltid = data[0] - '0';
        vector<long long> subpvs;
        string s;
        long long v;

        data = data.substr(1);
        if (ltid == 0) {
            long long subplen = stoll(data.substr(0, 15), 0, 2);
            data = data.substr(15);
            string subps = data.substr(0, subplen);
            while (subps.length()) {
                auto [s, v] = parse(subps);
                subps = s;
                subpvs.push_back(v);
            }
            data = data.substr(subplen);
        } else {
            long long subpqty = stoll(data.substr(0, 11), 0, 2);
            data = data.substr(11);
            for (long long i = 0; i < subpqty; i++) {
                auto [s, v] = parse(data);
                data = s;
                subpvs.push_back(v);
            }
        }

        if (tid == 0)
            return {data, accumulate(subpvs.begin(), subpvs.end(), 0ll)};
        else if (tid == 1)
            return {data, accumulate(subpvs.begin(), subpvs.end(), 1ll, multiplies<long long>())};
        else if (tid == 2)
            return {data, *min_element(subpvs.begin(), subpvs.end())};
        else if (tid == 3)
            return {data, *max_element(subpvs.begin(), subpvs.end())};
        else if (tid == 5)
            return {data, (subpvs[0] > subpvs[1] ? 1 : 0)};
        else if (tid == 6)
            return {data, (subpvs[0] < subpvs[1] ? 1 : 0)};
        else if (tid == 7)
            return {data, (subpvs[0] == subpvs[1] ? 1 : 0)};
    }
}

int main(int argc, char** argv) {
    string inp;
    cin >> inp;
    inp = HexToBin(inp);
    auto sol = parse(inp);
    cout << sol.second << '\n';
    return 0;
}