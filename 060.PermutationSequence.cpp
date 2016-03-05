[LeetCode 60] Permutation Sequence
The set [1, 2, 3, …, n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.

在面试时需要注意咨询面试官，输入的k 是否小于1 或者 是否大于n!

分析：按照一般的递归求全排列的算法（LeetCode:Permutations），
输出的序列不是按字典序有序的，比如对于1,2,3，输出序列为：

1 2 3
1 3 2
2 1 3
2 3 1
3 2 1
3 1 2

以3开头的排列举例，算法中是把1和3交换得到3 2 1，然后递归的求解，
但是3 2 1不是以3开头的最小序列，应该是3 1 2. 为了得到有序的序列，
我们不是把1 3 交换，而是应该把3移动到1的前面，
这样得到的第一个以3开头的序列就是3 1 2。因此有如下的算法：

算法1
class Solution {
private:
    int k_;
    string res_;
public:
    string getPermutation(int n, int k) {
        k_ = k;
        string str = string("123456789").substr(0, n);
        int cnt = 0;
        PermutationRecur(str, 0, cnt);
        return res_;
    }

    bool PermutationRecur(string &str, int index, int &cnt){
        int len = str.size();
        if(index == len - 1){
            cnt++;
            if(cnt == k_){
                res_ = str;
                return true;
            }
        }
        else{
            for(int i = index; i < len; i++){
                rotate(&str[index], &str[i], &str[i+1]);
                if(PermutationRecur(str, index + 1, cnt))
                    return true;
                rotate(&str[index], &str[i], &str[i+1]);
            }
        }
        return false;
    }
};
// 算法1在大数据下超时了。

算法2

利用next_permutation函数（该函数的详解请参考LeetCode:Permutations算法3），
但这种做法也超时了！
class Solution {
public:
    string getPermutation(int n, int k) {
        string str = string("123456789").substr(0, n);
        for(int i = 1; i <= k-1; i++)
            next_permutation(str.begin(), str.end());
        return str;
    }
};


算法3
上面的算法都是逐个的求排列，有没有什么方法不是逐个求，而是直接构造出第k个排列呢？
我们以n = 4，k = 17为例，数组src = [1, 2, 3, ..., n]。

第17个排列的第一个数是什么呢：我们知道以某个数固定开头的排列个数 = (n-1)! = 3! = 6,
即以1和2开头的排列总共6*2 = 12个，12 < 17, 因此第17个排列的第一个数不可能是1或者2，
6*3 > 17, 因此第17个排列的第一个数是3。即第17个排列的第一个数是原数组（原数组递增有序）
的第m = upper(17/6) = 3（upper表示向上取整）个数。                                           本文地址

第一个数固定后，我们从src数组中删除该数，那么就相当于在当前src的基础上
求第k - (m-1)*(n-1)! = 17 - 2*6 = 5个排列，因此可以递归的求解该问题。
class Solution {
public:
    string getPermutation(int n, int k) {
        string str = string("123456789").substr(0, n);
        string res(n, ' ');
        for(int i = 0; i < n; i++)
            res[i] = helper(str, k);
        return res;
    }
    //以s中字符构造的全排列中，返回第k个排列的第一个字符，并且删除s中该字符
    //s中字符递增有序
    char helper(string &s, int &k){
        int tmp = factorial(s.size()-1), i = (k-1)/tmp;
        char res = s[i];
        s.erase(i, 1);
        k -= i*tmp;	// 更新k
        return res;
    }
    //求正整数n的阶乘
    int factorial(int n){
        int res = 1;
        for(int i = 2; i <= n; i++)
            res *= i;
        return res;
    }
};

非递归实现
class Solution {
public:
    string getPermutation(int n, int k) {
        int total = factorial(n);
        string candidate = string("123456789").substr(0, n);
        string res(n,' ');
        for(int i = 0; i < n; i++){ // 依次计算排列的每个位
            total /= (n-i);
            int index = (k-1) / total;
            res[i] = candidate[index];
            candidate.erase(index, 1);
            k -= index*total;
        }
        return res;
    }
    int factorial(int n){
        int res = 1;
        for(int i = 2; i <= n; i++)
            res *= i;
        return res;
    }
};


其他解法(喜刷刷)：
思路：
同样先通过举例来获得更好的理解。以n = 4，k = 9为例：
1234
1243
1324
1342
1423
1432

2134
2143
2314  <= k = 9
2341
2413
2431

3124
3142
3214
3241
3412
3421

4123
4132
4213
4231
4312
4321

最高位可以取{1, 2, 3, 4}，而每个数重复(n-1)! = 3! = 6次。
所以第 k = 9 个permutation的s[0]为 {1, 2, 3, 4} 中的第 (9/6+1 = 2)个数字, 即s[0] = 2。
而对于以2开头的6个数字而言，k = 9是其中的第k' = 9%(3!) = 3个。 k' = k % (n-1)!
按照递归的思路，去掉开头的2不考虑之后，
剩下的数字{1, 3, 4}中的以每个数字开头的排列种数各有2! = 2次。
所以s[1]为{1, 3, 4}中的第(k'/(2!)+1 = 2)个，即s[1] = 3。
对于以23开头的2个数字(2314 和 2341)而言，k = 9是其中的第k'' = k'%(2!) = 1个。
剩下的数字{1, 4}中的以每个数字开头的排列种数各有1! = 1次。所以s[2] = 1.

对于以231开头的一个数字(只剩4了)而言，k = 9是其中的第k''' = k''/(1!)+1 = 1个。s[3] = 4

class Solution {
public:
    string getPermutation(int n, int k) {
        string ret;
        vector<int> factorial(n, 1);
        vector<char> num(n, 1);

        for(int i = 1; i < n; i++)
            factorial[i] = factorial[i - 1] * i;

        for(int i = 0; i < n; i++)
            num[i] = (i + 1) + '0';

        --k;
        for(int i = n; i >= 1; i--) {
            int j = k / factorial[i - 1];
            k %= factorial[i - 1];
            ret.push_back(num[j]);
            num.erase(num.begin() + j);
        }

        return ret;
    }
};