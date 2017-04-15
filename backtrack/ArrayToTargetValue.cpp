Backtracking

Problem :- 
Given a set of candidate values in an array & a target x, find all possible ways in which candidate values can be added to get x. We can use each candidate value any number of times.
Consider the candidate values as { 2, 3, 6, 7 } & target ( x ) = 8
Possible ways are :-
2 + 2 + 2 + 2 = 8
2 + 3 + 3 = 8
2 + 6 = 8 

Solution :- 
First we will find if there exists solution(s) starting from first candidate value and that value must be present in the solution one or more times.
We will start iterating over the candidate values and check if summing up those values lead to a solution. If at any point of iteration we exceed the target value, then we backtrack and try out other candidate values. This process continues till we find a solution.
Then we will move forward and try to find all solution(s) starting from second candidate value and again that value must be present in the solution. We will follow the same steps as described above.
See the implementation below.

#include<iostream>
using namespace std;

int MAX_SIZE;

// print the combination which evalutes to a given target
void printCombination(int candidates[],int comb[], int target,int comb_size) {
   cout<<endl;
   int i;
   for(i=0;i<comb_size;i++) {
      cout<<candidates[comb[i]];
      if(i < comb_size-1)
         cout<<" + ";
   }
}

// recursively compute all the possible combinations
int computeCombination(int candidates[],int size,int comb[],
                                        int target,int sum,int k,int j) {
   static int count = 0;
   if(sum > target) {
      // invalid combination     
      return -1;
   }
   if(sum == target) {
      // found a valid combination
      count++;
      printCombination(candidates,comb,target,j);
   }
   int i;
   for(i=k; i<size; i++) {
      comb[j] = k;
      computeCombination(candidates,size,comb,target,sum+candidates[i],k,j+1);
      k += 1;
   }
   return count;
}

// wrapper function
int solve(int candidates[], int size, int target) {
   // stores the indices of the 'candidate' elements
   int comb[MAX_SIZE];
   int count = computeCombination(candidates, size, comb, target, 0, 0, 0);
   return count;
}

// main
int main() {
   int candidates[] = {1, 2, 3, 6, 7};
   int size = sizeof(candidates)/sizeof(candidates[0]);
   int target = 8;
   MAX_SIZE = target/candidates[0]+1;
   cout<<"\nPossible combinations are :-\n";
   int num_of_ways = solve(candidates, size, target);
   cout<<"\n\nNo. of possible ways :: "<<num_of_ways;
   cout<<endl;
   return 0;
}