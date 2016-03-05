// https://www.quora.com/Given-an-array-of-n-elements-what-is-a-linear-time-algorithm-that-finds-all-elements-that-appear-more-than-n-3-times
Given an array of n elements, what is a linear-time algorithm that finds all elements that appear more than n/3 times?


Analysis:
Find a median m_0 of the whole array A[1]...A[N]. This can be done in O(n) time by the median-of-five algorithm.
Partition the array around m_0; so that all values < m_0 occur before m_0, and values >= m_0 occur after m_0. (Yes, this is exactly what quicksort does).
Find medians m_1, m_2 for subarrays A[1]..A[i], A[i+1]...A[N] (i is the position of m_0).
Count how many times does m_0, m_1 and m_2 occur in A. (3x linear search). Output whichever of them occurs more than N/3-times.

Why?
If we sorted A, there would be a sequence of same values, at least N/3 elements long.
Any such sequence must be split by either of the 3 medians we selected, as the space between any 2 of them is only N/4 elements long.
Thus each value that occurs more than N/3 times in the array, must be either m_0, m_1 or m_2.


Here is an alternate randomized approach that might be easier to understand:
Pick n√ elements uniformly at random, find the 4 most frequent elements using brute force (or sorting if that's allowed). 
Check each of these 4 and report any of them that appears more than n/3 times.
There can be at most 2 elements that appear more than n/3 times. 
For each of them, Chernoff bound gives that the probability of it appearing in fewer than 1/4 of the samples 
is less than n−c for any constant c. The union bound then gives that this succeeds with high probability.

This approach is slower, and has a non-zero failure probability. 
So if you want to code this, the routine that Mark mentioned is the way to go.

// another inplementation
The paper cited above generalizes the idea from the question and can help you find all elements 
that occur with frequency greater than n/k in O(n log k) time.  
In fact this algorithm can identify k-1 elements as the only elements that could occur more than n/k times 
online (though another pass is required to confirm they each occur more than n/k times). 
But before we get to the more complicated version of the problem consider the simple version where k=2.  
In this version we're interested in identifying a majority element.
Here we keep two registers, one indicating our candidate majority element, call it y, (initialized to whatever) 
and another keeps a count, call it cnt, (initialized to 0).  The algorithm proceeds online.
Suppose we read the integer x.  If cnt is 0 we set y = x.  Next if x = y we increment cnt, otherwise we decrement it.
Now I claim that if a majority element exists it will be y.  However there is no way to know if y really is a majority 
element online with constant memory so we need to do another scan and count how many times y actually occurs.  
This of course is really easy.
So why does the algorithm do as I claim?  For purpose of analysis consider anytime that y!=z that cnt is negative.  
Then any time we read in z we increment cnt and whenever we read in something else we may increment or decrement cnt.  
Because z is the majority element it's clear we always increment more than decrement.
The generic algorithm (in section 3 of the paper) builds off of this and makes use of a multiset t initialized to the empty set.
When we read an element x we insert it into t.  If t now contains k elements we remove each unique element of t once.
At the end t contains all elements that could have occurred more than n/k times.  
Even the naive version of this algorithm runs in O(n log k) time amortized.  
Then we can verify in O(n log k) time as well.

The algorithm thus takes O(nlogk) time overall. For the special case of k=3, this reduces to O(n).

/* Moves all elements that appear more than n/k times to the front of the range.
 * Returns the end of this range of elements.
 * O(n log k) time using O(k) memory. */
template<class FIterator>
FIterator find_repeats(FIterator first, FIterator last, int k) {
  /* Compute the candidate elements in one pass. */
  int N = 0;
  std::map<typeof(*first), int> count;
  for(FIterator it = first; it != last; ++it, ++N) {
    ++count[*it];
    if(count.size() == k) {
      for(typeof(count.begin()) jt = count.begin(), tmp; jt != count.end(); ) {
        tmp = jt++;
        if(--tmp->second == 0) {
          count.erase(tmp);
        }
      }
    }
  }

  /* Verify the candidate elements in a second pass. */
  FIterator result = first;
  std::map<typeof(*first), int> candidate_count;
  for(FIterator it = first; it != last; ++it) {
    if(count.find(*it) != count.end() && ++candidate_count[*it] == N / k + 1) {
      std::swap(*result++, *it);
    }
  }
  std::sort(first, result);
  return result;
}

int main() {
  int N = 10;
  int A[] = {7, 6, 6, 8, 5, 3, 6, 2, 8, 1};
  int M = find_repeats(A, A + N, 4) - A;
  for(int i = 0; i < M; i++) {
    std::cout << A[i] << std::endl;
  }
  return 0;
}