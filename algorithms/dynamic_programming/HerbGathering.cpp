// 动态规划
采药问题
1. 首先以采摘的时间为阶段。
2. 确立状态及状态变量：totaltime时间内采摘sum种药品获得的最大价值。
3. 决策：如果采摘第i种药品获得的价值大于不采摘的情况，
    最大价值等于采摘第i种药品获得的价值；反之，最大价值等于不采摘第i种药品获得的价值。
4. 状态转移方程：
max【t】=max{value[i] + max[t-time[i]],max[t-1]}

#include <stdio.h>
int totalTime, medics;
int value[100];
int time[100];
int max[1001]; //全局变量默认的初值均为0，所以max【0】为该解的出口。
int main(){
    scanf("%d%d", &totalTime, &medics);
    int i, t;
    for (i=0; i<medics; i++){
        scanf("%d%d", &time[i], &value[i]);
    }

    for (i=0; i<medics; i++){
        for (t=totalTime; t>0; t--){
            if (time[i] <= t){
                if (value[i] + max[t-time[i]] > max[t]){             //第i个的价值+不选第i个且用时为t-time[i-1]时最大价值
                    max[t] = value[i] + max[t-time[i]];
                }
            }
        }
    }
    printf("%d\n", max[totalTime]);
    return 0;
}