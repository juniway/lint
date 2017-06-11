#include <cmath>
#include <vector>
#include <string>
#include <bitset>
#include <iostream>

using namespace std;

// 二进制方式求集合所有子集
class Set {
public:
    void get_all_subsets(const string& origin) {
        //获取将要分解的字符串如果转为2进制最大是几
        //如字符串是3位，就是2^3。从[0 0 0]到[1 1 1]
        origin_ = origin;
        unsigned maxLen = pow(2, origin_.length());
        subsets_.resize(maxLen);

        for (unsigned i = 0; i < subsets_.size(); i++) {
            subsets_[i] = dec2int(i);
        }

        convert();
    }



private:
    string dec2int(unsigned int n) {
        string result = bitset<sizeof(n)*8>(n).to_string();
        string::size_type x = result.find('1');
        if (x != string::npos) {
            result = result.substr(x);
        } else {
            result = "0";
        }
        return result;
    }

    void convert(){
        for (int i = 0; i < (int)subsets_.size(); ++i) {
            string& s = subsets_[i];
            int n = s.length(), m = origin_.length();
            for (int j = 0; j < n; ++j) {
                s[n - j - 1] = s[n - j - 1] == '1' ? origin_[m - j - 1] : ' ';
            }
        }
        print();
    }

    void print() {
        for (auto &i : subsets_) {
            cout << i << endl;
        }
    }

    string origin_;
    vector<string> subsets_;
};

int main() {
    Set s;
    s.get_all_subsets("abc");
}

