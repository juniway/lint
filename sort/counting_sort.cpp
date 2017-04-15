
// counting sort
// the input has a limited value, for example, input sequence numbers are between 1 ~ 100.
// Time: O(N) Space: O(N)

string sortStr(const string &str) {
    static unsigned int b[26];
    for (unsigned int i = 0; i < str.length(); ++i) {
        ++b[str[i]-'a'];
    }

    // 排序
    string tmp;
    for (unsigned int i = 0; i < 26; ++i) {
        for (unsigned int j = 0; j < b[i]; ++j) {
            tmp += (char)('a' + i);
        }
    }

    return tmp;
}

