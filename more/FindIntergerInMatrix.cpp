class Solution {
public:
    bool FindInterger(int (*arr)[4], int row, int col, int s) {
        int i = 0, j = col - 1;
        while (i < row && j >= 0){
            if (s > arr[i][j]){
                i++;
                continue;
            } else if (s < arr[i][j]){
                j--;
                continue;
            } else{
                return true;
            }
        }
        if (i == row || j < 0){
            return false;
        }
        return true;
    }
};