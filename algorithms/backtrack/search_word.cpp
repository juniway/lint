bool searchWord(char[][] matrix, String word) {
    int N = matrix.length;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (search(matrix, word, i, j, 0, N)) {
                return true;
            }
        }
    }
    return false;
}

// 可以走 8 个方向
bool search(char matrix[][], string word, int row, int col, int index, int N) {

    // check if current cell not already used or character in it is not
    if (solution[row][col] != 0 || word[index] != matrix[row][col]) {
        return false;
    }

    if (index == word.length() - 1) {
        solution[row][col] = path++;        // word is found, return true
        return true;
    }

    // mark the current cell as 1
    solution[row][col] = path++;

    if (row + 1 < N && search(matrix, word, row + 1, col, index + 1, N)) {  // go down
        return true;
    }
    if (row - 1 >= 0 && search(matrix, word, row - 1, col, index + 1, N)) { // go up
        return true;
    }
    if (col + 1 < N && search(matrix, word, row, col + 1, index + 1, N)) { // go right
        return true;
    }
    if (col - 1 >= 0 && search(matrix, word, row, col - 1, index + 1, N)) { // go left
        return true;
    }

    if (row - 1 >= 0 && col + 1 < N && search(matrix, word, row - 1, col + 1, index + 1, N)) { // go diagonally up right
        return true;
    }
    if (row - 1 >= 0 && col - 1 >= 0 && search(matrix, word, row - 1, col - 1, index + 1, N)) { // go diagonally up left
        return true;
    }
    if (row + 1 < N && col - 1 >= 0 && search(matrix, word, row + 1, col - 1, index + 1, N)) { // go diagonally down left
        return true;
    }
    if (row + 1 < N && col + 1 < N && search(matrix, word, row + 1, col + 1, index + 1, N)) { // go diagonally down right
        return true;
    }

    // if none of the option works out, BACKTRACK and return false
    solution[row][col] = 0;
    path--;
    return false;
}

void main(String[] args) {
    char matrix[][] = {
        { 't', 'z', 'x', 'c', 'd' },
        { 'a', 'h', 'n', 'z', 'x' },
        { 'h', 'w', 'o', 'i', 'o' },
        { 'o', 'r', 'n', 'r', 'n' },
        { 'a', 'b', 'r', 'i', 'n' }
    };

    WordMatrix w = new WordMatrix(matrix.length);
    if (w.searchWord(matrix, "horizon")) {
        w.print();
    } else {
        printf("NO PATH FOUND\n");
    }

}