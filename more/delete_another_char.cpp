//从一个字符串中删除另一个字符串中出现的字符

#include <stdio.h>

void delete_char(char *a, char *b)
{
	if(a==NULL || b==NULL)
		return;
	char hash_table[256] = {0};//创建简单哈希数组，存储字符串b中每个字符出现的次数
	char *p = b;
	while(*p != '\0')
		hash_table[*p++]++;
	char *fast = a;
	char *slow = a;
	while(*fast != '\0')
	{
		if(hash_table[*fast]==1)//如果该字符是字符串b中出现的，则指针直接++
		{
			fast++;
		}
		else//否则，将其值赋给*slow
		{
			*slow++ = *fast++;
		}
	}
	*slow = '\0';//别忘了给结尾赋'\0'
}

int main()
{
	char a[] = "we are students";
	char b[] = "aeiou";
	printf("%s中删除%s中出现的字符，结果是:\n",a,b);
	delete_char(a,b);
	printf("%s\n",a);
	return 0;
}