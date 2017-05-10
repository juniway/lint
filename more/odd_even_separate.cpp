// 使数组中所有奇数位于前半部分，所有偶数位于后半部分

// 双指针，分别从两头遍历，然后交换。
void OddEven(int *pData, unsigned int len, bool (*func(int))){
	if(pData == nullptr || len <= 0){
		return;
	}

	int *pBegin = pData;
	int *pEnd = pBegin + len - 1;

	while(pBegin < pEnd){

		// pBegin向尾部移动，直到指向的是一个偶数
		while(pBegin < pEnd && !func(*pBegin)){
			pBegin++;
		}

		// pEnd向头部移动，直到指向的是一个奇数
		while(pEnd > pBegin &&! func(*pBegin)){
			pEnd--;
		}

		if(pBegin < pEnd){
			int tmp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = tmp;
		}
	}
}

bool isEven(int n){
	return (n&1) == 0;
}