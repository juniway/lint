/*
[lintcode]
Given an unsorted array of integers, 
find the length of the longest consecutive elements sequence.

Example
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Clarification
Your algorithm should run in O(n) complexity.
*/

class Solution{
public:
    /**
    * @param A[]: A list of integers
    * @return an integer
    */
    int longestConsecutive(vector<int> &A) {
                // write you code here
        unordered_set<int> myset;

        for (int i : A) {
            myset.insert(i);
        }
        
        int maxLen = 0;
        for(auto i : A) {
        	int count = 1;
        	myset.erase(i);

        	int tmp = i;
        	while(myset.find(tmp - 1) != myset.end()){
        		myset.erase(tmp - 1);
        		tmp--;
        		count++;
        	}

        	tmp = i;
        	while(myset.find(tmp + 1) != myset.end()){
        		myset.erase(tmp + 1);
        		tmp++;
        		count++;
        	}
        	maxLen = max(maxLen, count);
        }
        return maxLen;


        for (int i = 0; i < (int)A.size(); ++i){
            if (myset.find(A[i]) != myset.end()){  //遍历每个数，当A[i]在set中存在
                int next = A[i] - 1;      // 继续找比A[i]小1的值
                int count = 1;
                myset.erase(A[i]);         //及时移除, 以免后续重复查找
                while (myset.find(next) != myset.end()){ //A[i] - 1也在set中存在
                    myset.erase(next);
                    next--;
                    count++;
                }
                next = A[i] + 1;      // 找比A[i]大1的值
                while (myset.find(next) != myset.end()){
                    myset.erase(next);
                    next++;
                    count++;
                }
                maxLen = std::max(maxLen, count);
            }
        }

        return maxLen;
    }
};

