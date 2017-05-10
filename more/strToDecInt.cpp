#include<stdio.h>
#include<cctype>

int StrtoDecInt(const char* str){
    static const int MAX = (int)((unsigned)~0 >> 1);
	static const int MIN = -(int)((unsigned)~0 >> 1) - 1;

	unsigned int n = 0;
	int sign = 1;
	unsigned int c;

	while (isspace(*str))  // skip the preceeding space charactors
		++str;

	if(*str == '-' || *str == '+'){
		if(*str == '-')
			sign = -1;
		++str;
	}

	while(isdigit(*str)){
		c = *str - '0';
		if(sign > 0 && (n > MAX/10 || (n == MAX/10 && c > MAX % 10))) { // 考虑最大的正数
			n = MAX;
			break;
		} else if (sign < 0 && (n > (unsigned) MIN/10 || (n== (unsigned) MIN/10 && c > (unsigned) MIN % 10))){ // 最小的负数
			n = MIN;
			break;
		}
		n = n*10 + c;
		++str;
	}
	return sign > 0 ? n : -n;
}

int main(){
	const char* numstr="331";
	int num = StrtoDecInt(numstr);
	printf("number is : %d\n", num);
	return 0;
}