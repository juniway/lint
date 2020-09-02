#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Coder {
public:
    vector<string> findCoder(vector<string> A, int n) {
        // write code here

        vector<pair<int, int>> st;

        string coder = "CODER";
        for (string::size_type i = 0; i < A.size(); i++) {
            string::size_type pos = 0;
            int cnt = 0;
            string tmp = A[i];
            transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
            while((pos = tmp.find(coder, pos)) != string::npos) {
                cnt++;
                pos = pos + coder.size();
            }
            cout << "cnt: " << cnt;
            st.push_back(make_pair(i, cnt));
        }

        auto cmp = [](const pair<int, int> p1, const pair<int, int> p2) {
            return p1.second > p2.second;
        };
        stable_sort(st.begin(), st.end(), cmp);
        vector<string> res;
        for(auto it = st.begin(); it != st.end(); it++)
            res.push_back(A[it->first]);

        return res;
    }
};

void testFindCoder() {
    vector<string> A = {
        "Coder",
        "coder, coder====",
    };
    Coder sol;
    auto res = sol.findCoder(A, 4);
    for (auto s : res) cout << s << ", "; cout << endl;
}

int main(int argc, char *argv[]) {
    testFindCoder();
    return 0;
}

