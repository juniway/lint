// 妙趣横生的算法(c语言实现) page 89
// 回溯

#include <stdio.h>

int count = 0;        // 解的个数

int isCorrect(int i, int j, int (*Q)[4]) { // is Q[i][j] correct
	int s, t;
	for(s = i, t = 0; t < 4; ++t){ 					// 检查该行中，第 j 列之前，是否已经放过。
		if(Q[s][t] == 1 && t != j) return 0;
	}

	for(t = j, s = 0; s < 4; ++s){ 					// 检查该列中，第 i 行之前，是否已经放过。
		if((Q[s][t] == 1 && s != i)) return 0;
	}

	for(s = i - 1, t = j - 1; s >= 0 && t >= 0; --s, --t){ // 检查左上方，是否已经放过。
		if(Q[s][t] == 1) return 0;
	}

	// for(s = i + 1, t = j + 1; s < 4 && t < 4; ++s, ++t){ // 检查右下方，是否已经放过。 其实可以不必检查，因为右下方还没放过。
	// 	if(Q[s][t] == 1) return 0;
	// }

	for(s = i - 1, t = j + 1; s >= 0 && t < 4; --s, ++t){ // 检查右上方，是否已经放过。
		if(Q[s][t] == 1) return 0;
	}

	for(s = i + 1, t = j -1 ; s <4 && t >= 0; ++s, --t){ // 检查左下方，是否已经放过。
		if(Q[s][t] == 1) return 0;
	}

	return 1;  //  succeed
}

bool queen4(int j, int (*Q)[4]) { // 按列遍历处理，每次递归，遍历一列，然后在内部循环处理每一行。
	int i, k;
	if(j == 4) { 						// 所有列都遍历万，打印结果
		for(i = 0; i < 4; ++i){
			for(k = 0; k < 4; ++k)
				printf("%d ", Q[i][k]);
			printf("\n");
		}
		printf("\n");
		++count;
		return true;
	}

	for(i = 0; i < 4; ++i) {
		// 遍历每一行，看 i, j 位置是否可以放置一个 queen，如果可以，则递归到下一列，如果不可以，则试试下一行，
		// 如果该列的每一行都不行，那么最终会跳出循环，回到递归的上一层，会把上一层的 Q[i][j] unset。
		if(isCorrect(i, j, Q)){
			Q[i][j] = 1;
			if(queen4(j + 1, Q)) return true;
			else
				Q[i][j] = 0;
		}
	}
	return false;
}

int main(){
	int Q[4][4];
	int i, j;
	for(i = 0; i < 4; ++i)
		for(j = 0; j < 4; ++j)
			Q[i][j] = 0;
	queen4(0, Q);
	printf("The number of the answers of Four_QUEEN are %d\n", count);
}