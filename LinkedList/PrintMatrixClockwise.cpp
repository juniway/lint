/*
1	2	3	4
5	6	7	8
9	10	11	12
13	14	15	16

*/

// print: 1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10


void printMatrixOutline(int **, int, int, int);

void PrintMatrixClockwise(int  **matrix, int rows, int cols){
	if(rows < = 0 || cols <= 0 || matrix == nullptr) return;

	int start = 0;
	while(rows > start*2 && cols > start*2){
		printMatrixOutline(matrix, rows, cols, start);
		start++;
	}

}

void printMatrixOutline(int **matrix, int rows, int cols, int start){

	int endx = cols - 1 - start;
	int endy = rows - 1 - start;

	// left -> right
	for(int i = start; i <= endx; ++i){
		printf("%d ", matrix[start][i]);
	}

	// top -> bottom
	if(start < endy){
		for(int i = start + 1; i <= endy, ++i){
			printf("%d", matrix[i][endx]);
		}
	}


	// right -> left
	for(int i = cols - 1; i >= start; --i){
		printf("%d ", matrix[rows - 1][i]);
	}

	// bottom -> top
	for(int i = rows - 1; i > start + 1; --i){
		printf("%d ", matrix[i][start]);
	}
}