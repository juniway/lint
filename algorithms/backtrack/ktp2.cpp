#include <iostream>
#include <iomanip>  //setw()的头文件
#define N 8        //定义一个宏并赋初值
using namespace std;
int tour[N][N];    //定义全局性的二维数组保存步数
// bool a[N][N];   //记录某一点是否已经走过, false 表示没走过

int sol_cnt = 0;      //记录方案数
int dx[] = {1,  1, -1, -1, 2,  2, -2, -2};  // 对应骑士可走的8个方向
int dy[] = {2, -2,  2, -2, 1, -1,  1, -1};  // 提供每一步的走法

bool isMoveOK(int x1, int y1, int tour[N][N]){
	if((x1 >= 0 && x1 < N) && (y1 >= 0 && y1 < N)&& tour[x1][y1] == 0)
		return true;
	return false;
}

void print(){
    ++sol_cnt;     //方案数加一
    cout << "方案数：" << sol_cnt << " :" << endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << setw(4)<< tour[i][j]; //依次输出经过每一点时的步数
        }
        cout << endl;
    }
}

bool solve1(int x, int y, int k){ //计算走法
    cout << "k =" << k << endl;
    if(k == N * N - 1){
        print();
        ++sol_cnt;
        return true;
    }

    int x1, y1;
    for(int i = 0; i < N; ++i){ // 一共有 8 个方向的走法，分别遍历这些走法，一个不行就试另外一个。
        x1 = x + dx[i];
        y1 = y + dy[i];
        if(isMoveOK(x1, y1, tour)){
            tour[x1][y1] = k + 1;
            if(solve1(x1, y1, k + 1)){
                return true;
            }
            else{
                tour[x1][y1] = 0;
            }

        }
    }
    return false;
}

void solve(int x, int y, int k){ //计算走法
    cout << "k =" << k << endl;
    if(k == N * N - 1){
        print();
        ++sol_cnt;
        return;
    }

    int x1, y1;
    for(int i = 0; i < N; ++i){ // 一共有 8 个方向的走法，分别遍历这些走法，一个不行就试另外一个。
        x1 = x + dx[i];
        y1 = y + dy[i];
        if(isMoveOK(x1, y1, tour)){
            tour[x1][y1] = k + 1;
            solve(x1, y1, k + 1);
            tour[x1][y1] = 0;
        }
    }
    return;
}

int main(){
    int i, j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++)
            tour[i][j] = false;
    }

    // b[0][0] = 0; //设置起始点
    // tour[0][0] = true;
    solve(0, 0, 0);
    // if(solve (0, 0, 0))  //调用函数计算结果
    //     cout << "succeed\n";
    // else
    //     cout << "failed\n";

    return 0;
}