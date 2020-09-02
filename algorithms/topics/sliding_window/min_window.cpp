/* Leetcoce 76
 * Minimum Window Substring
 *
 * */
#include <climits>
#include <string>
#include <vector>

using std::string;
using std::vector;

string minWindow(string s, string t) {
    vector<int> map(128, 0);

    for(auto a:t) {
        map[a]++;
    }

    int begin = 0, end = 0, head = 0, d = INT_MAX, count = t.size();
    while(end < s.size()) {
        if(map[s[end++]]-- > 0) count--;
        while(count == 0) {
            d = std::min(d, end - (head = begin));
            if (map[s[begin++]]++ == 0) count++;
        }
    }

    return d == INT_MAX? "" : s.substr(head, d);
}
