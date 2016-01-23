[LeetCode 239] Sliding Window Maximum
Given an array A, there is a sliding window of size k which is moving from the very left of the array to the very right. 
You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given A = [1, 3, -1, -3, 5, 3, 6, 7], and k = 3.

Window position                Max 
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return an array which consist of the max element of each sliding window as [3, 3, 5, 5, 6, 7].

Note: 
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?

Hint:
How about using a data structure such as deque (double-ended queue)?
The queue size need not be the same as the window’s size.
Remove redundant elements and the queue should store only elements that need to be considered.

这道题给定了一个数组，还给了一个窗口大小k，让我们每次向右滑动一个数字，每次返回窗口内的数字的最大值，
而且要求我们代码的时间复杂度为O(n)。提示我们要用双向队列deque来解题，并提示我们窗口中只留下有用的值，
没用的全移除掉。
果然Hard的题目我就是不会做，网上看到了别人的解法才明白，解法又巧妙有简洁，膜拜啊。
大概思路是用双向队列保存数字的下标，遍历整个数组，如果此时队列的首元素是i - k的话，表示此时窗口向右移了一步，
则移除队首元素。然后比较队尾元素和将要进来的值，如果小的话就都移除，然后此时我们把队首元素加入结果中即可，
'

遍历数组A，使用双端队列deque维护滑动窗口内有可能成为最大值元素的数组下标
由于数组中的每一个元素至多只会入队、出队一次，因此均摊时间复杂度为O(n)
记当前下标为i，则滑动窗口的有效下标范围为[i - (k - 1), i]
若deque中的元素下标＜ i - (k - 1)，则将其从队头弹出，deque中的元素按照下标递增顺序从队尾入队。
这样就确保deque中的数组下标范围为[i - (k - 1), i]，满足滑动窗口的要求。
当下标i从队尾入队时，顺次弹出队列尾部不大于A[i]的数组下标（这些被弹出的元素由于新元素的加入而变得没有意义）
deque的队头元素即为当前滑动窗口的最大值

代码如下：
// python
class Solution:
    def maxSlidingWindow(self, A, k):
        dq = collections.deque()
        ans = []
        for i in range(len(A)):
            while dq and A[dq[-1]] <= A[i]:
                dq.pop()
            dq.append(i)
            if dq[0] == i - k:
                dq.popleft()
            if i >= k - 1:
                ans.append(A[dq[0]])
        return ans
// c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& A, int k) {
        vector<int> res;
        deque<int> q;
        for (int i = 0; i < A.size(); ++i) {
            while (!q.empty() && A[q.back()] < A[i]) q.pop_back();
            q.push_back(i);

            if (!q.empty() && q.front() == i - k) q.pop_front();
            if (i >= k - 1) res.push_back(A[q.front()]);
        }
        return res;
    }
};

