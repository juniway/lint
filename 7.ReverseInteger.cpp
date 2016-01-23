// [LeetCode 7] Reverse Integer

// Reverse digits of an integer.

// Example1: x = 123, return 321
// Example2: x = -123, return -321

// Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!
// If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.
// Did you notice that the reversed integer might overflow? 
// Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. 
// How should you handle such cases?
// For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
// Update (2014-11-10):
// Test cases had been added to test the overflow behavior.

int reverse(int x) {
	long long tmp = x;
	long long result =0;
	int lastdigit = 0;
	// bool isNeg = x < 0 ? true: false;
	tmp = abs(tmp);
	while(tmp != 0)
	{  
		lastdigit = tmp%10;  
		result = result*10 + lastdigit;  
		tmp = tmp/10;  
	}
	if(result > std::numeric_limits<int>::max())
	    return 0;
    // if(isNeg)
    //     result *= -1;
	return result;
}