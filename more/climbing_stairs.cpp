[LeetCode 70] Climbing Stairs
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Diffyculty: easy
class Solution {
public:
    int climbStairs(int n) {
        int a1 = 1, a2 = 1;
        
        for(int i = 2; i <= n; ++i){
            int temp = a1 + a2;
            a1 = a2;
            a2 = temp;
        }
        return a2;
    }
};