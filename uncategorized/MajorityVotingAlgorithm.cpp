Boyer and Moore

This algorithm, which Bob Boyer and I invented in 1980 decides which element of a sequence is in the majority, provided there is such an element.
How would you determine the majority element of:
sequence:  A A A C C B B C C C B C C
You could count the number of occurrences of each element. Here is how we do it, in one pass.

这个算法是解决这样一个问题：从一个数组中找出出现半数以上的元素

A A A C C B B C C C B C C
^
0
We will sweep down the sequence starting at the pointer position shown above.

As we sweep we maintain a pair consisting of a current candidate and a counter.
Initially, the current candidate is unknown and the counter is 0.

When we move the pointer forward over an element e:

If the counter is 0, we set the current candidate to e and we set the counter to 1.
If the counter is not 0, we increment or decrement the counter according to whether
e is the current candidate.
When we are done, the current candidate is the majority element, if there is a majority.

The algorithm only works when the set has a majority
which means more than half of the elements being the same.

1). first part of running Moore's Voting algorithm only gives you A candidate
	which occurs "most" of the time in the given array. Notice the "most" here.
2). In the second part, we need to iterate over the array once again to determine
	if this candidate occurs maximum number of times (i.e. greater than size/2 times).'

需要part2的原因是最后剩下的元素也可能并没有出现半数以上。
比如说AAACCBB，最后剩下的B显然只出现了2次，并不到半数。
int this case, there is no majority. becasue the most frequent letter occurs 3 times,
while the string length is 7.

int Voting(vector<int> &num){
    int count = 0;
    int candidate;

    for(int i = 0; i < num.size(); ++i) {
        if(count == 0) {
            candidate = num[i];
            count = 1;
        }
        else
            count = (candidate == num[i]) ? ++count : --count;
    }
    return candidate;
}

int IsMajorityElement(vector<int> A, int candidate)
{
    int cnt = 0;
    int i;
    for(i = 0; i < n; i++){
	    if(A[i] == candidate)
	        ++cnt;
    }
    if(cnt > n/2)
    	return 1;
    else
    	return 0;
}

// another problem
// find the element in an array that occur most frequently

int MostFrequentValue(vector<int> A) {
	int n = A.size();
    int maxKey = 0;
    int maxCounts = 0;

    int counts[n];

    for (int i = 0; i < n; i++) {
        counts[n[i]]++;
        if (maxCounts < counts[n[i]]) {
            maxCounts = counts[n[i]];
            maxKey = n[i];
        }
    }
    return maxKey;
}

int main(String[] args) {
    int[] n = new int[] {3, 7, 4, 1, 3, 8, 9, 3, 7, 1};
    cout << mode(n) << endl;
}
