#include <stdio.h>
#include <string.h>
#define N 8

int board[N][N] = {0};
int ktmove1[8] = { 1,  2, 2, 1, -1, -2, -2, -1};    // 对应骑士可走的8个方向
int ktmove2[8] = {-2, -1, 1, 2,  2,  1, -1, -2};
int nexti[8] = {0};                                 // 测试下一步的出路
int nextj[8] = {0};
int exits[8] = {0};                                 // 记录出路的格个数

int travel(int x, int y) {
    int i,j,k,m,l,tmpi,tmpj,tmp,min,cnt;
    memset(ktmove1, 0, sizeof(ktmove1));
    memset(ktmove2, 0, sizeof(ktmove2));
    memset(exits, 0, sizeof(exits));
    i = x;
    j = y;
    board[i][j] = 1;
    for(m=2; m<=N*N; m++) {
        k = 0;
        //试探8个方向
        for(l=0; l<8; l++) {
            tmpi = i + ktmove1[l];
            tmpj = j + ktmove2[l];
            if(tmpi<0 || tmpj<0 || tmpi>7 || tmpj>7)
                continue;
            if(board[tmpi][tmpj]==0) {
                nexti[k] = tmpi;
                nextj[k] = tmpj;
                k++;
            }
        }
        cnt = k;
        if(cnt==0) return 0;        //如果可走的方向为0，返回
        else if(cnt==1) min = 0;    //如果可走的方向为1，直接是出路最少的方向
        else {
            //找下一个位置的出路数
            for(l=0; l<cnt; l++) {
                for(k=0; k<8; k++) {
                    tmpi = nexti[l] + ktmove1[k];
                    tmpj = nextj[l] + ktmove2[k];
                    if(tmpi<0 || tmpj<0 || tmpi>7 || tmpj>7)
                        continue;
                    if(board[tmpi][tmpj]==0)
                        exits[l]++;
                }
            }
            tmp = exits[0];
            min = 0;
            //可走方向中寻找最少出路的方向
            for(l=1; l<cnt; l++)
                if(exits[l] < tmp) {
                    tmp = exits[l];
                    min = 1;
                }
        }
        //走最少出路的方向
        i = nexti[min];
        j = nextj[min];
        board[i][j] = m;
    }
    return 1;
}

int main() {
    int sx = 0, sy = 0;
    //输入起始点
    // if(sx<1 || sy<1 || sx>N || sy>N) break;
    if(travel(sx, sy))
        printf("Travel finished!\n");
    else
        printf("Travel falled!\n");
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            printf("%2d ", board[i][j]);
        }
    puts("");
    }
    return 0;
}