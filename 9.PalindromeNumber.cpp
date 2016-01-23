// [LeetCode 9] Palindrome Number

// 不断地取第一位和最后一位（10进制下）进行比较，相等则取第二位和倒数第二位，直到完成比较或者中途找到了不一致的位。
// 可以避免造成溢出，因为只是首尾digit比较。

class Solution {
public:
    bool isPalindrome(int x) {
    	// negative number is not palimdrome
    	if(x < 0) return false;
    	int div = 1;
    	while(x / div >= 10){
    		div *= 10;
    	}
    
    	while(x > 0){
    		int lastdigit = x % 10;
    		int firstdigit = (x / div) % 10;
    		if(lastdigit != firstdigit)
    			return false;
    		x = (x % div) / 10;
    		div /= 100;
    
    	}
    	return true;
    }
};