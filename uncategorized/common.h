#include <cmath>
#include <vector>
#include <string>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

// 二进制方式求集合所有子集
// 0 - 1 knapsack
class knapsack {
public:
    vector<vector<int>> get_all_subsets(const vector<int> & origin) {
        origin_ = origin;
        unsigned maxLen = pow(2, origin_.size());
        subsets_.resize(maxLen);

        for (unsigned i = 0; i < subsets_.size(); i++) {
            subsets_[i] = dec2int(i);
        }

        return convert();
    }

    void print(const vector<int>& all) {
        for (auto &i : all) {
            cout << i << endl;
        }
    }

    void printall(const vector<vector<int>>& all) {
        for (auto &i : all) {
            for (auto &j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
    }

private:
    vector<vector<int>> convert(){

        vector<vector<int>> all;
        vector<int> line;

        for (int i = 0; i < (int)subsets_.size(); ++i) {
            string& s = subsets_[i];
            int n = s.length(), m = origin_.size();
            for (int j = 0; j < n; ++j) {
                if (s[n - j - 1] == '1')
                    line.push_back(origin_[m - j - 1]);
                else
                    line.push_back(0);
            }
            all.push_back(line);
            line.clear();
        }
        printall(all);

        return all;
    }

    string dec2int(unsigned n) {
    string result = bitset<sizeof(n)*8>(n).to_string();
    string::size_type x = result.find('1');
    if (x != string::npos) {
        result = result.substr(x);
    } else {
        result = "0";
    }
    return result;
    }



    vector<int> origin_;
    vector<string> subsets_;
};

int main() {

    vector<int> weights = {5, 4, 6, 3};
    vector<int> values = {10, 40, 30, 50};
    int cap = 10;

    knapsack s;
    vector<vector<int>> weight_subsets = s.get_all_subsets(weights);
    vector<vector<int>> legit;
    copy_if(weight_subsets.begin(), weight_subsets.end(), std::back_inserter(legit), [&cap](vector<int> a) {return accumulate(a.begin(), a.end(),0) <= cap;});
    cout << "==================" << endl;
    s.printall(legit);

    vector<int> all;
    for (auto &i: legit) {
        vector<int> res;
        transform(i.begin(), i.end(), values.begin(), back_inserter(res), [](int a, int b) {return a*b;});
        all.push_back(accumulate(res.begin(), res.end(), 0));
    }

    cout << "==================" << endl;
    s.print(all);

}

