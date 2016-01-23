[LeetCode 299] Bulls and Cows
You are playing the following Bulls and Cows game with your friend: 
You write a 4-digit secret number and ask your friend to guess it, 
each time your friend guesses a number, you give a hint, 
the hint tells your friend how many digits are in the correct positions (called "bulls") and 
how many digits are in the wrong positions (called "cows"), 
your friend will use those hints to find out the secret number.

For example:
Secret number:  1807
Friend's guess: 7810
Hint: 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)

 

According to Wikipedia: "Bulls and Cows (also known as Cows and Bulls 
or Pigs and Bulls or Bulls and Cleots) is an old code-breaking mind or paper and 
pencil game for two or more players, predating the similar commercially marketed 
board game Mastermind. The numerical version of the game is usually played with 4 digits, 
but can also be played with 3 or any other number of digits."

Write a function to return a hint according to the secret number and friend's guess, 
use A to indicate the bulls and B to indicate the cows, in the above example, 
your function should return 1A3B.

You may assume that the secret number and your friend's guess only contain digits, 
and their lengths are always equal.

这道题提出了一个叫公牛母牛的游戏，有一个四位数字，你猜一个结果，然后根据你猜的结果和真实结果做对比，
提示有多少个数字和位置都正确的叫做bulls，还提示有多少数字正确但位置不对的叫做cows，
根据这些信息来引导我们继续猜测正确的数字。
这道题并没有让我们实现整个游戏，而只用实现一次比较即可。给出两个字符串，
让我们找出分别几个bulls和cows。
这题需要用哈希表，来建立数字和其出现次数的映射。我最开始想的方法是用两次遍历，
第一次遍历找出所有位置相同且值相同的数字，即bulls，并且记录secret中不是bulls的数字出现的次数。
然后第二次遍历我们针对guess中不是bulls的位置，如果在哈希表中存在，cows自增1，然后映射值减1，
参见如下代码：

class Solution {
public:
    string getHint(string secret, string guess) {
        int m[256] = {0}, bulls = 0, cows = 0;
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] == guess[i]) ++bulls;
            else {
                if (m[secret[i]]++ < 0) ++cows;
                if (m[guess[i]]-- > 0) ++ cows;
            }
        }
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};