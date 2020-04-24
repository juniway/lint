//第一个只出现一次的字符

#include <stdio.h>

char find(const char *str)
{
	if(str==NULL)
		return '\0';
	int hash_table[256] = {0};//创建简单哈希数组，下标是字符的ASCII值，数组值是字符出现的次数
	const char *p = str;
	while(*p != '\0')
		hash_table[*p++]++;
	p = str;
	while(*p != '\0')
	{
		if(hash_table[*p]==1)//找到只出现一次的字符
			return *p;
		p++;
	}
	return '\0';
}

int main()
{
	char *str = "abaccdeff";
	char result = find(str);
	printf("%s中第一个只出现一次的字符是%c\n",str,result);
	return 0;
}
