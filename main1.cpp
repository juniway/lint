#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <limits>
#include <stack>
#include <cstring>
#include <set>

using namespace std;

// void quicksort(int A[], int begin, int end){

//  int i = begin, j = end;
//  if (i > j) return;

//  while(i < j){
//      while(a[j] > a[end] && j > i){
//          --j;
//      }
//      while(a[i] < a[end] && i > j){
//          ++i;
//      }
//      if(i < j)
//          swap(a[i], a[j]);
//  }

//  int temp = a[end];
//  a[end] = a[i];
//  a[i] = temp;

//  quicksort(A, begin, i - 1);
//  quicksort(A, i + 1, end);
// }

// void Partition(int A[], int start, int end){
//  if(A == nullptr || start > end) return;
//  int index = start - 1;
//  for(int i = start; i < end - 1; ++i){
//      if(A[i] < A[end]){
//          ++index;
//          if(index != i)
//              Swap(A[index], A[i]);
//      }
//  }

//  return ++index;
// }

// same as remove duplicate

// void findDistinct(vector<int>& A){
//     int n = A.size();

//     int index = 2;
//     for(int i = 2; i < n; ++i){
//         if(A[index - 2] == A[i])
//          A[index++] = A[i];
//     }
// }
template <typename T>
void print(const vector<T>& A){
    for(auto &i: A){
        cout << i << " ";
    }
    cout << endl;
}

// Given a center, either one letter or two letter,
// Find longest palindrome
string longestpal_at_pos(string s, int begin, int end) {
    while (begin >= 0 && end <= (int)s.length() - 1 && s[begin] == s[end]) {
        begin--;
        end++;
    }
    return s.substr(begin + 1, end - begin - 1);
}


string longestPalindrome(string s) {
        int n = s.length();
        if (n == 0) return "";
        if (n == 1) return s;

        string longest = s.substr(0, 1);
        for (int i = 0; i < n; i++) {
            // get longest palindrome with center of i
            string tmp = longestpal_at_pos(s, i, i); // odd
            if (tmp.length() > longest.length()) {
                longest = tmp;
            }

            // get longest palindrome with center of i, i+1
            tmp = longestpal_at_pos(s, i, i + 1);
            if (tmp.length() > longest.length()) {
                longest = tmp;
            }
        }

        return longest;
}

void bubblesort(vector<int>& A){
    int n = A.size();
    int count = 0;
    bool swapped = false;
    for(int i = 0; i < n; ++i){
        for(int j = 1; j < n - i; ++j){
            if(A[j - 1] > A[j]){
                swap(A[j - 1], A[j]);
                ++count;
                swapped = true;
            }
        }
        if(!swapped) break;
    }
    cout << "count:" << count <<"|";
    print(A);

}

void insertionsort(vector<int>& A){
    int n = A.size();
    for(int i = 0; i < n; ++i){
        int j = i;
        while(j > 0 && A[j] < A[j - 1]){
            swap(A[j], A[j - 1]);
            --j;
        }
    }
    print(A);
}

void selectsort(vector<int>& A){
    int n = A.size();
    for(int i = 0; i < n; ++i){
        for(int j = i; j < n; ++j){
            if(A[j] < A[i])
                swap(A[j], A[i]);
        }
    }
    print(A);
}

int myAtoi(string str) {
        long long result = 0;
        bool isNeg = false;
        for(auto &c:str){
            if(c == '+' || c == '-'){
                if(c == str.front()){
                    if(c == '-')
                        isNeg = true;

                }
                else{
                    return 0;
                }
                continue;
            }
            if(c >= '0' && '9'){
                result = result * 10 + (c - '0');
                cout << result << endl;
            }
            else{
                return 0;
            }
        }

        if(isNeg)
            result *= -1;
        return result;
}

bool isValid(string s) {
    stack<char> st;
    for(int i = 0; i < (int)s.length(); ++i){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            st.push(s[i]);
        }
        else{
            if(s[i] == ')' && st.top() != '(')
                return false;
            else if(s[i] == ']' && st.top() != '[')
                return false;
            else if(s[i] == '}' && st.top() != '{')
                return false;
            else
                st.pop();
        }
    }
    return st.empty();
}

void NextPermutation(vector<int> &A){
    int n = A.size();
    int k = n - 1;
    while(k > 0){
        if(A[k - 1] < A[k]) break;
        k--;
    }
    if(k == 0){
        for(int i = 0, j = n - 1; i < j; i++, j--){
            swap(A[i], A[j]);
        }
    }

    // scan from the end of the vector<>,
    // and swap the smallest element that are greater than A[k-1]
    int s = n - 1;
    for(; s >= k; s--){
        if(A[s] > A[k-1]){
            swap(A[s], A[k-1]);
            break;
        }
    }

    // sort the remaining A[k] to A[n-1]
    sort(A.begin() + k, A.end());
}

string longestcommonprefix(vector<string>& strs){
    int n = strs.size();
    if(n == 0) return string();

    for(int i = 0; i < (int)strs[0].size(); ++i){
        for(int j = 1; j < n; ++j){
            if(i == (int)strs[j].size() || strs[0][i] != strs[j][i]){
                return strs[0].substr(0, i);
            }
        }
    }
    return strs[0];
}

// bool isMatch(const char *s, const char *p){
//  if(p == nullptr)
//      return s == nullptr;
//  if(*(p+1) == '*'){
//      return isMatch(s, p+2) || (*p == '.' && *s != '\0' || *p == *s) && isMatch(s + 1, p);
//  }
//  if(*p == '.')
//      return *s && isMatch(s+1, p + 1);
//  return *s == *p && isMatch(s + 1, p + 1);
// }

// string getsubpal(string& str, int begin, int end){
//  while(begin >= 0 && end < str.length() && str[begin - 1] == str[end + 1]){
//      begin--;
//      end++;
//  }
//  return str.substr(being + 1, end - begin - 1);
// }

// string longestPalindrome(string& str){
//  int n = str.length();
//  if(n == 0) return string();
//  if(n == 1) return str;

//  string result;
//  for(int i = 0; i < n; ++i){
//      string longestpal = str[0];
//      string tmp = getsubpal(str, i, i);
//      longestpal = max(longestpal.length(), tmp.length());

//      tmp = getsubpal(str, i, i + 1));
//      longestpal = max(longestpal.length(), tmp.length());
//  }

//  return result
// }


bool isMatchWildCard(const string& w, const string& s){
    int m = w.length(), n = s.length();
    int pos = 0;
    while(pos < m && pos < n && (w[pos] == '?' || w[pos] == s[pos]))
        ++pos;
    if(pos == m) return pos == n;
    if(w[pos] == '*'){
        for(int i = 0; pos + i < n; ++i){
            if(isMatchWildCard(w.substr(pos + 1), s.substr(pos + i)));
                return true;
        }
    }
    return false;
}


// detect whether a ip is valid
#define DELIM "."

bool valid_digit(char *ip_str){
    char *p = ip_str;
    while (*p) {
        if (*p >= '0' && *p <= '9')
            ++p;
        else
            return false;
    }
    return atoi(p) >= 0 && atoi(p) <= 255;
}

// return 1 if IP string is valid, else return 0
bool is_valid_ip(char *ip_str){
    int dots = 0;
    char *ptr;
    if (ip_str == nullptr)
        return false;

    ptr = strtok(ip_str, DELIM);

    if (ptr == nullptr)
        return false;

    while (ptr) {
        // after parsing string, it must contain only digits
        if (!valid_digit(ptr))
            return false;
        // num = atoi(ptr);
        // parse remaining string
        ptr = strtok(nullptr, DELIM);
        if (ptr != nullptr)
            ++dots;
    }

    // valid IP string must contain 3 dots
    if (dots != 3)
        return false;
    return true;
}

int search_rotate(vector<int>& A, int target) {
    int n = (int)A.size();
    int l = 0, r = n - 1;
    while(l <= r){
        int mid = l + (r - l)/2;
        if(target == A[mid]) return mid;
        if(A[mid] < A[l]){
            if(target >= A[mid] && target < A[r])
                l = mid  + 1;
            else r = mid - 1;
        }
        else{
            if(target <= A[mid] && target > A[l])
                r = mid - 1;
            else
                l = mid + 1;
        }
    }
    return -1;
}
void getNext(vector<int> &next, string &needle) {
    int n = needle.length() - 1;
    int i = 0, j = -1;
    next[i] = j;
    while (i < n) {
        while (j != -1 && needle[i] != needle[j])
            j = next[j];
        ++i; ++j;
        //特殊情况，这里即为优化之处。考虑下AAAAB, 防止4个A形成0123在匹配时多次迭代。
        // if (needle[i] == needle[j])
        //  next[i] = next[j];
        // else
            next[i] = j;
    }
}

int strStr(string haystack, string needle) {
    int n = haystack.length(), m = needle.length();

    if (haystack.empty()) return needle.empty() ? 0 : -1;
    if (needle.empty()) return 0;
    vector<int> next(m + 1);
    getNext(next, needle);
    int i = 0, j = 0;
    while (i != n) {
        while (j != -1 && haystack[i] != needle[j]) j = next[j];
        ++i; ++j;
        if (j == m) return i - j;
    }
    return -1;
}

// class Solution {
// public:
//     vector<vector<int> > combine(int n, int k) {
//         vector<vector<int> > result;
//         vector<int> path;
//         dfs(n, k, 1, 0, path, result); // 1, 2, 3, 4
//         return result;
//     }

// private:
//  // start，开始的数, cur，已经选择的数目
//  static void dfs(int n, int k, int start, int cur,
//  vector<int> &path, vector<vector<int> > &result){
//      if (cur == k){
//          cout << cur << endl;
//          result.push_back(path);
//      }

//      for (int i = start; i <= n; ++i){
//          path.push_back(i);
//          dfs(n, k, i + 1, cur + 1, path, result);
//          path.pop_back();
//      }
//  }
// };

class Solution {
public:
    std::vector<std::vector<int> > combinationSum2(std::vector<int> &candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> res;
        std::vector<int> combination;
        combinationSum2(0, candidates, target, combination, res);
        return res;
    }
private:
    void combinationSum2(int begin, std::vector<int> &candidates, int target, std::vector<int> &combination, std::vector<std::vector<int> > &res) {
        if(target == 0){ // 相当于sum == target
            res.push_back(combination);
            return;
        }
        for (int i = begin; i < (int)candidates.size() && target >= candidates[i]; ++i){
            if (i == begin || candidates[i] != candidates[i - 1]) {
                combination.push_back(candidates[i]);
                combinationSum2(i + 1, candidates, target - candidates[i], combination, res);
                combination.pop_back();
            }
        }
    }
};

// void permute(string select, string remain, vector<string> &result){
//  // int n = remain.size();
//  if(remain == ""){
//      result.push_back(select);
//      return;
//  }

//  for(int i = 0; remain[i] != '\0'; ++i){
//      string wk(remain);
//      permute(select + remain[i], remain.erase(i, 1), result);
//  }
// }

// int MostFrequentValue(vector<int> A) {
//  int n = A.size();
//     int maxKey = 0;
//     int maxCounts = 0;

//     // std::dynarray<int> counts(n);
//     // int counts[n];
//     vector<int> counts(n, 0);

//     for (int i = 0; i < n; i++) {
//         counts[A[i]]++;
//         if (maxCounts < counts[A[i]]) {
//             maxCounts = counts[A[i]];
//             maxKey = A[i];
//         }
//     }
//     return maxKey;
// }

// int moore_voting(vector<int> &A){
//     int count = 0;
//     int candidate;

//     for(int i = 0; i < A.size(); ++i) {
//         if(count == 0) {
//             candidate = A[i];
//             count = 1;
//         }
//         else
//             count = (candidate == A[i]) ? ++count : --count;
//     }
//     return candidate;
// }

// int IsMajorityElement(vector<int> A, int candidate){
//     int cnt = 0;
//     int i;
//     for(i = 0; i < n; i++){
//      if(A[i] == candidate)
//          ++cnt;
//     }
//     if(cnt > n/2)
//      return 1;
//     else
//      return 0;
// }

// [
//      [2],
//     [3,4],
//    [6,5,7],
//   [4,1,8,3]
// ]

int minimumTotal(vector<vector<int> > &triangle) {
    int row = triangle.size();
    if(row == 0) return 0;
    vector<int> minV(triangle[row - 1].size());
    for(int i = row - 1; i >= 0; i--){
        int col = triangle[i].size();
        for(int j = 0; j < col; j++){
            if(i == row - 1){
                minV[j] = triangle[i][j];
                continue;
            }
            minV[j] = min(minV[j], minV[j + 1]) + triangle[i][j];
        }
    }
    return minV[0];
}

int firstMissingPositive(vector<int>& A) {
    int n = A.size();
    int i=0;
    while(i < n) {
        if(A[i] > 0 && A[i] <= n && A[i] != i+1 && A[i] != A[A[i] - 1])
            swap(A[i], A[A[i] - 1]);
        else
            i++;
    }

    print(A);
    for(int i = 0; i < n; i++) {
        if(A[i] != i + 1) return i+1;
    }
    return n+1;
}

// int triangleMin(vector<int> &A){
//  int row = A.size();
//  if(row == 0) return 0;

//  vector<int> minV((int)A[row - 1].size(), 0);
//  for(int i = row - 1; i >= 0; --i){
//      int col = A[i].size();
//      for(int j = 0; j < col; ++j){
//          if(i == row - 1) minV[j] = A[i][j];
//          else
//              minV[j] = min(minV[j], minV[j+1]) + A[i][j];
//      }
//  }
//  return minV[0];
// }

string minWindow(string S, string T) {
        int n1 = S.length(), n2 = T.length();
        if (n1 == 0 || n2 == 0) return "";

        int count = T.size();
        int require[128] = {0};
        bool IsInPattern[128] = {false};

        for (int i = 0; i < count; ++i){
            ++require[T[i] - 'a'];
            IsInPattern[T[i] - 'a'] = true;
        }
        // use i to loop the String, j denotes the tart index
        // initially j is 0
        int i = -1, j = 0;
        int minIdx = 0, minLen = numeric_limits<int>::max();
        while (i < n1 && j < n1){
            if (count > 0){
                i++;
                --require[S[i] - 'a'];
                if (IsInPattern[S[i] - 'a'] && require[S[i] - 'a'] >= 0) // 如果字符'A'被找到了，并且没有需要再找的'A'
                    count--;
            }
            else{
                int currentLen = i - j + 1;
                if (currentLen < minLen){
                    minLen = currentLen;
                    minIdx = j;
                }
                ++require[S[j] - 'a'];
                if (IsInPattern[S[j] - 'a'] && require[S[j] - 'a'] > 0) // shrink
                    count++;
                j++;
            }
        }
        if (minLen == numeric_limits<int>::max()) return "";
        return S.substr(minIdx, minLen);
}

class Solution_1 {
public:
    vector<vector<int>> permuteUnique(vector<int>& A) {
        if(A.empty()) return {{}};
        sort(A.begin(), A.end());
        set<int> st;

        vector<vector<int>> result;
        permuteUnique(A, 0, result, st);
        return result;
    }
    void permuteUnique(vector<int>& A, int start, vector<vector<int>>& res, set<int>& st){
        int pre_size = st.size();
        st.insert(A[start]);
        if((int)st.size() > pre_size) ++start;

        int n = A.size();
        if(start == n){
            res.push_back(A);
            return;
        }
        for(int i = start; i < n; ++i){
            if(i > 0 && A[i] == A[i - 1]) continue;
            swap(A[start], A[i]);
            permuteUnique(A, start + 1, res, st);
            swap(A[start], A[i]);
        }
    }
};


class Solution2{
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> sol;

        vector<int> col(n, -1);
        solver(n, 0, col, sol, res);

        return res;
    }
    void solver(int n, int irow, vector<int> &col, vector<string> &sol, vector<vector<string>> &res){
        if(irow == n){
            res.push_back(sol);
            return;
        }
        for(int icol = 0; icol < n; ++icol){
            if(isValid(irow, icol, col)){
                string s(n, '.');
                s[icol] = 'Q';
                sol.push_back(s);
                // col.push_back(icol);
                col[irow] = icol;
                solver(n, irow + 1, col, sol, res);
                sol.pop_back();
                col[irow] = -1;
                // col.pop_back();
            }
        }
    }

    bool isValid(int irow, int icol, vector<int> &col){
        for(int i = 0; i < irow; ++i){
            if(icol == col[i] || abs(irow - i) == abs(icol - col[i])) {
                cout << "i = " << i << ", col[i] = " << col[i] << endl;
                cout <<"icol = " << icol << endl;
                cout << "irow - i = " << irow - i << ", icol - col[i] = " << icol - col[i] << endl;
                return false;
            }
        }
        return true;
    }
};

class Solution3 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;

        std::sort(strs.begin(), strs.end()); //
        for(auto& e: strs){
            cout << e << ",";
        }
        cout << endl;

        map<string, vector<string>> codeToStrs;
        for(int i = 0; i < (int)strs.size(); i++){
            codeToStrs[getCode(strs[i])].push_back(strs[i]);
        }

        for(auto it = codeToStrs.begin(); it!= codeToStrs.end(); it++){
            result.push_back(it->second);
        }

        return result;
    }

    string getCode(string s){
        std::sort(s.begin(), s.end());
        return s;
    }
};

class Sol3sum {
public:
    vector<vector<int>> threeSum(vector<int> & nums){
        int n = nums.size();
        vector<vector<int>> triples;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 2; ++i){
            if(i > 0 && nums[i] == nums[i - 1]) continue;
            twoSum(nums, i + 1, 0 - nums[i], triples);
        }
        return triples;
    }

    // void twoSum(vector<int> &nums, int start, int target, vector<vector<int>> &res){
    //     for(int i = start + 1; i < (int)nums.size(); ++i){
    //         int val = target - nums[i];
    //         if(hash.find(val) != hash.end()){
    //             res.push_back({nums[start], nums[i], val});
    //             continue;
    //         }
    //         hash[nums[i]] = i;
    //     }

    // }

    void twoSum(vector<int> &nums, int start, int target, vector<vector<int>> &res){
        int i = start, j = (int)nums.size() - 1;

        while(i < j){
            int sum = nums[i] + nums[j];
            if(sum == target) {
                res.push_back({nums[start - 1], nums[i], nums[j]});
                ++i;
                --j;
                while(nums[i] == nums[i - 1]) ++i;
                while(nums[j] == nums[j + 1]) --j;
            }
            else if(sum < target) ++i;
            else --j;
        }
    }
};

class Sol4sum {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        vector<vector<int>> tetrads;
        if(nums.size() < 4) return tetrads;
        sort(nums.begin(), nums.end());

        for(int i = 0; i < (int)nums.size() - 3; ++i){
            if(i > 0 && nums[i] == nums[i - 1]) continue;
            for(int j = i + 1; j < (int)nums.size() - 2; ++j){
                if(j > 1 && i != j - 1 && nums[j] == nums[j - 1]) continue;
                twoSum(nums, i, j + 1, target - nums[i] - nums[j], tetrads);
            }
        }

        return tetrads;
    }

    void twoSum(vector<int> &nums, int start0, int start1, int target, vector<vector<int>> &tetrads){
        int i = start1, j = (int)nums.size() - 1;
        while(i < j){
            int sum = nums[i] + nums[j];
            if(sum == target){
                tetrads.push_back({nums[start0], nums[start1 - 1], nums[i], nums[j]});
                ++i; --j;
                while(nums[i] == nums[i - 1]) ++i;
                while(nums[j] == nums[j + 1]) --j;
            }
            else if(sum < target) ++i;
            else --j;
        }
    }
};

class Sol4sumrec{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target){
        vector<vector<int>> allSol;
        vector<int> sol;
        sort(nums.begin(), nums.end());
        kSum(nums, 4, 0, nums.size() - 1, target, sol, allSol);

        return allSol;
    }

    void kSum(vector<int> &nums, int k, int start, int end, int target, vector<int> &sol, vector<vector<int>> &allSol){
        if(k <= 0) return;
        if(k == 1) {
            for(int i = start; i <= end; ++i){
                sol.push_back(nums[i]);
                allSol.push_back(sol);
                sol.pop_back();
                return;
            }
        }
        if(k == 2){
            twoSum(nums, start, end, target, sol, allSol);
            return;
        }

        for(int i = start; i <= end - k + 1; ++i){
            if(i > start && nums[i] == nums[i - 1]) continue;
            sol.push_back(nums[i]);
            kSum(nums, i + 1, end, target - nums[i], k - 1, sol, allSol);
            sol.pop_back();
        }
    }

    void twoSum(vector<int> & nums, int start, int end, int target, vector<int> &sol, vector<vector<int>> &allSol){

        while(start < end){
            int sum = nums[start] + nums[end];
            if(sum == target){
                sol.push_back(nums[start]);
                sol.push_back(nums[end]);
                allSol.push_back(sol);
                sol.pop_back();
                sol.pop_back();
                ++start; --end;
                while(nums[start] == nums[start - 1]) ++start;
                while(nums[end] == nums[end + 1]) --end;
            }
            else if(sum < target) ++start;
            else --end;
        }
    }
};

// ==============================================================================================

int main(){
    // vector<int> vec = {1, 2, 3, 3, 5, 6, 6, 6};
    // findDistinct(vec);

    // string s{"abcbe"};
    // string res = longestPalindrome(s);

    // vector<int> vec1 = {7, 9, -1, 19, 6, 11, 2, 22, 8, 4};
    // vector<int> vec2 = {1, 2, 3, 4, 7, 11, 13, 14, 19, 22};
    // vector<int> vec3 = {22, 18, 15, 7, 6, 4, 3, 2, 1, 0};
    // bubblesort(vec1);
    // bubblesort(vec2);
    // bubblesort(vec3);
    // myAtoi(s);

    // Solution sol;
    // string s = "";
    // vector<string> result = sol.letterCombinations(s);
    // std::cout << std::noboolalpha << f << std::boolalpha << t << std::endl;
    // vector<int> permu = {7, 8, 6, 9, 8, 7, 2};
    // NextPermutation(permu);
    // print(permu);

    // string w = "c*a*b", s = "aab";
    // cout << std::boolalpha << isMatchWildCard(w, s) << endl;

    // char ip[][20] = {"192.168.1.", "192.168.1.1", "01.3.1.1"};
    // int i = -1;
    // while(i++<2){
    //  cout << ip[i] << ": ";
    //  cout << std::boolalpha << is_valid_ip(ip[i]) << endl;
    // }

    // string s = "ABCD BABCDABD";
    // string p = "ABCDABD";
    // strStr(s, p);

    // Solution s;
    // vector<vector<int>> v =  s.combine(4, 2);

    // for(auto &e:v){
    //  cout << "[";
    //  for(auto &e1:e){
    //      cout << e1;
    //  }
    //  cout <<"]\n";
    // }
    // cout << endl;

    // Solution s;
    // vector<int> v = {1, 1, 2, 5, 6, 7, 10};
    // vector<vector<int>> res = s.combinationSum2(v, 8);

    // string abc = "abc";
    // string str = "";
    // vector<string> result;
    // permute(str, abc, result);
    // for(auto &e: result){
    //  cout << e;
    // }
    // cout << endl;

    // vector<int> A = {2, 2, 2, 2, 3, 3, 3, 6, 6, 6, 6, 6};
    // cout << MostFrequentValue(A) << endl;


    // vector<int> A = {-2, -3, -1, 0, 2, 3, 4};
    // cout << firstMissingPositive(A) << endl;

    // vector<vector<int>> A = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    // cout << minimumTotal(A) << endl;
    // string S = "ADOBECODEBANC";
    // string T = "ABC";
    // cout << minWindow(S, T) << endl;

    // vector<int> A = {1, 1};
    // Solution_1 s;
    // vector<vector<int>> res = s.permuteUnique(A);
    // for(auto &e:res){
    //  print(e);
    // }
    // cout << endl;

    // Solution2 s2;
    // s2.solveNQueens(4);

    // vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    // Solution3 s3;
    // s3.groupAnagrams(strs);

    // vector<int> input = {-14,-10,-1,8,-8,-7,-3,-2,14,10,3,3,-1,-15,6,9,-1,6,-2,-6,-8,-15,8,-3,-14,5,-1,-12,-10,-5,-9,-8,1,-3,-15,0,-3,-11,6,-11,7,-6,7,-9,-6,-10,7,1,11,-10,10,-12,-10,3,-7,-9,-7,7,-14,-9,10,14,-2,-4,-4,-10,3,1,-14,-6,5,8,-4,-11,14,-3,-6,-2,13,13,3,0,-14,8,10,-14,6,11,1,7,-13,-4,6,0,-1,10,-3,-13,-4,-2,-11,8,-8};
    // vector<int> input = {0, 0, 0};
    // vector<int> input = {-2, 0, 1, 1, 2};
    // vector<int> input = {1, 2, -2, -1};

    vector<int> input = {0,-1,0,1,-2,-5,3,5,0};

    Sol4sum s4;
    vector<vector<int>> result = s4.fourSum(input, 6);
    for(auto row : result){
        cout << endl;
        for(auto i : row) cout << i << " ";
    }
    cout << "\nsize: " << result.size() << endl;

}
