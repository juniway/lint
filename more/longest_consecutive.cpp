class Solution04 {
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

        for (int i = 0; i < (int)A.size(); ++i){
            if (myset.find(A[i]) != myset.end()){  //±éÀúÃ¿¸öÊý£¬µ±A[i]ÔÚsetÖÐ´æÔÚ
                int next = A[i] - 1;      // ¼ÌÐøÕÒ±ÈA[i]Ð¡1µÄÖµ
                int count = 1;
                myset.erase(A[i]);         //¼°Ê±ÒÆ³ý, ÒÔÃâºóÐøÖØ¸´²éÕÒ
                while (myset.find(next) != myset.end()){ //A[i] - 1Ò²ÔÚsetÖÐ´æÔÚ
                    myset.erase(next);
                    next--;
                    count++;
                }
                next = A[i] + 1;      // ÕÒ±ÈA[i]´ó1µÄÖµ
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