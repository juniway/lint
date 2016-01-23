#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char* add_big_int(char* num1, char* num2){
	int carry = 0;
	int i = strlen(num1) - 1;
	int j = strlen(num2) - 1;
	int max_len = i > j ? (i + 1) : (j + 1);
	
	char* result = (char*)malloc(max_len + 1); // save result
	if(result = NULL) return -1;
	result[max_len] = '\0';

	int k = strlen(v) - 1;
	while((i >= 0) && (j >= 0)){
		int val = (num[i] - '0') + (num2[j] - '0');
		result[k] = (val + carry) % 10 + '0';
		carry = val / 10;
		--i;
		--j;
		--k;
	}

	while(i > 0){ // len1 > len2
		result[k] = ((num2[i] - '0') + carry) % 10 + '0';
		carry = (num2[i] - '0' + carry) / 10;
		--i;
		--k;
	}

	while(j > 0){ // len1 > len2
		result[k] = ((num2[i] - '0') + carry) % 10 + '0';
		carry = (num2[j] - '0' + carry) / 10;
		--j;
		--k;
	}
	result[0] = carry + '0';

	if(result[0] != '0') // 如果结果最高位不等于0， 则直接输出结果
		return result;
	else
		return result + 1;

}

int main(){
	char num1[] = "12345678923";
	char num2[] = "45671254563123";
	char *result = NULL;
	result = add_big_int(num1, num2);
	printf("%s + %s = %s\n", num1, num2, result);
	return 0;
}