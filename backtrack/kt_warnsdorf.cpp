// Warnsdorff’s Rule: Always move to an adjacent, unvisited square with minimal degree.
// The logic behind is this: 
// since squares with lower degrees have fewer neighbors and therefore we will have 
// fewer opportunities to visit them in the remainder of the path

#include <stdio.h>
#include <string.h>
#define N 8

int board[N][N] = {0};
int ktmove1[8] = { 1,  2, 2, 1, -1, -2, -2, -1};    // 对应骑士可走的8个方向
int ktmove2[8] = {-2, -1, 1, 2,  2,  1, -1, -2};
int nexti[8] = {0};                                 // 保存可走的下一步的位置
int nextj[8] = {0};
int exits[8] = {0};                                 // 记录出路的格个数

bool isMoveOK(int x1, int y1){
    if(x1 < 0 || x1 >= N || y1 < 0 || y1 >= N || board[x1][y1] != 0){
        // printf("(%d, %d) Can't move\n", x1, y1);
        return false;
    }
    // printf("(%d, %d) move ok\n", x1, y1);
    return true;
}

void print(int len){
    for(int i = 0; i <= len; ++i){
        printf("(%d, %d)\n", nexti[i], nextj[i]);
    }
}

bool travel(int x, int y) {
    int k, tmp, min, cnt;
    // memset(ktmove1, 0, sizeof(ktmove1));
    // memset(ktmove2, 0, sizeof(ktmove2));
    // memset(exits, 0, sizeof(exits));

    int x1, y1;
    board[x][y] = 1;                                // board[i][j] = 1说明已经走过
    int i, j;
    for(i = 2; i <= N*N - 1; i++) {
        k = 0;
        // 试探8个方向, 找出可走的是哪几个方向
        for(j = 0; j < 8; j++) {
            x1 = x + ktmove1[j];
            y1 = y + ktmove2[j];
            if(isMoveOK(x1, y1)){
                nexti[k] = x1;
                nextj[k] = y1;
                k++;
            }
        }

        // print(k);
        // getchar();
        cnt = k;
        if(cnt == 0) return 0;          // 如果可走的方向数量为0，说明结束，返回
        else if(cnt == 1) min = 0;      // 如果可走的方向为1，直接是出路最少的方向
        else {
            // 找下一个位置的出路数, 保存在exits[j]中
            for(j = 0; j < cnt; j++) {
                for(k = 0; k < 8; k++) {
                    x1 = nexti[j] + ktmove1[k];
                    y1 = nextj[j] + ktmove2[k];
                    if(isMoveOK(x1, y1))
                        exits[j]++;

                    // if(tmpi<0 || tmpj<0 || tmpi>7 || tmpj>7)
                    //     continue;
                    // if(board[tmpi][tmpj]==0)
                }
            }
            tmp = exits[0];
            min = 0;
            // 可走方向中寻找最少出路的方向
            for(j = 0; j < cnt; j++)
                if(exits[j] < tmp) {
                    tmp = exits[j];
                    min = j;
                }
        }
        //走最少出路的方向
        x1 = nexti[min];
        y1 = nextj[min];
        board[x1][y1] = i;
        x = x1, y = y1;
    }
    return true;
}

int main() {
    int sx, sy, i, j;
    //输入起始点
    while(scanf("%d%d", &sx, &sy)!=EOF){
        if(sx < 0 || sy < 0 || sx > N - 1 || sy > N - 1) break;
        if(travel(sx, sy))
            printf("Travel finished!\n");
        else
            printf("Travel falled!\n");
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                printf("%2d ", board[i][j]);
            }
        puts("");
        }
    }
    return 0;
}