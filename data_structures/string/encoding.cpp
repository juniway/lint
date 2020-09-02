#include <iostream>
#include <vector>
#include <string>

using namespace std;

string compress(string s) {
    int start = 0;
    string res;
    for (int j = start; j < s.length();) {
        res += s[j];
        while (j < s.length() && s[j] == s[start]) {
            j++;
        }

        if ((j - start) > 2)
            res += to_string(j - start);
        else res += s.substr(start, j - start - 1);

        start = j;
    }
    return res;
}

string compress1(string s) {
    int count = 1;
    string res;
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == s[i + 1]) {
            count++;
        } else {
            res = res + s[i] + to_string(count);
            count = 1;
        }
    }

    res = res + s.back() + to_string(count);
    return res.length() < s.length() ? res : s;
}

vector<string> encoding(vector<string>& strs) {
    if (strs.empty()) return {};
    vector<string> res;
    for (int i = 0; i < strs.size(); i++) {
        int start = 0;
        string tmp;
        for (int j = start; j < strs[i].size();) {
            while (strs[i][j] == strs[i][start]) {
                j++;
            }
            int len = j - start;
            if (len > 2) {
                tmp.push_back(len + '0');
            }
            tmp.push_back(strs[i][start]);
            start = j;
        }
        res.push_back(tmp);
    }
    return res;
}

vector<string> encoding1(int n, vector<string>& strs) {
    for (int i = 0; i < n; i++) {
        int start = 0, k = 0;
        int j = start + 1;
        for (; j < strs[i].size();) {
            if (strs[i][j] == strs[i][start]) {
                j++;
            } else {
                int len = j - start;
                if (len > 1) {
                    strs[i][k] = len + '0';
                    strs[i][k + 1] = strs[i][j - 1];
                    k += 2;
                } else {
                    strs[i][k] = strs[i][start];
                    k += 1;
                }
                start = j;
                j++;
            }
        }
        int len = j - start;
        if (len > 1) {
            strs[i][k] = len + '0';
            strs[i][k + 1] = strs[i][j - 1];
            k += 2;
        } else {
            strs[i][k] = strs[i][start];
            k += 1;
        }
        strs[i] = strs[i].substr(0, k + 1);
    }

    return strs;
}

void testEncoding() {
    vector<string> strs = {
        {"ABC"}, {"ABBCCC"}
    };

    auto res = encoding(strs);

    for (auto s : res) {
        cout << s << " ";
    }
    cout << endl;
}

void testCompress() {
    string s = "AABBBB   CCCD";
    cout << compress(s) << endl;
    cout << compress1(s) << endl;
}

int main(int argc, char *argv[]) {
    // testEncoding();
    testCompress();
    return 0;
}
