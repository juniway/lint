#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


// 思路概述：
// 有序地从第 1 列的第 1 行开始，尝试放上一个皇后，然后再尝试第 2 列的第几行能够放上一个皇后，如果第 2 列也放置成功，那么就继续放置第 3 列，如果此时第 3 列没有一行可以放置一个皇后，说明目前为止的尝试是无效的（即不可能得到最终解），那么此时就应该回溯到上一步（即第 2 步），将上一步（第 2 步）所放置的皇后的位置再重新取走放在另一个符合要求的地方…如此尝试性地遍历加上回溯，就可以慢慢地逼近最终解。
// 共有92种解法

class NQueen {
public:
    static int index;

    void show(vector<int> queen){
        for(int i = 0; i < (int)queen.size(); i++){
            for (int j = 0; j < kN; ++j) {
                if (j == queen[i]) {
                    cout << j;
                } else cout << " ";
                // cout << queen[i] << " " << endl;
            }
            cout << endl;
        }
        cout << endl;
        index++;
    }

     // k 表示行，i 表示列
    void process(vector<int> queen, int k){ // queen[k] 表示在第 k 行放置一个皇后
        if(k == 8){ // 找到解了
            show(queen);
            return;
        }
        for(int i = 0; i < kN; i++){
            if(!check(queen, k, i)) // 在第 k 行中，不断检测第 i 个元素是否可以放置。
                continue;
            else {
                queen[k] = i;  // 放置皇后 k
                process(queen, k+1); // 放置皇后 k+1
                queen[k] = -1; // 更好地表示回溯 会被覆盖的
            }
        }
    }

    // 新皇后放入的位置
    bool check(vector<int> queen, int row, int col){
        for(int i = 0; i < row; i++)
            if(queen[i] == col) return false; // 水平及垂直方向检测
        for(int i = 0; i < row; i++)
            if(row - i == abs(col - queen[i])) return false; // 对角线检测
        return true;
    }

private:
    static const int kN = 8;
};

int NQueen::index = 0;

int main() {
    NQueen queen;
    vector<int> v(8, -1);
    queen.process(v, 0);
    cout << "共有" << NQueen::index << "种解法" << endl;
}