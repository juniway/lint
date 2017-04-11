//删除字符串中所有重复出现的字符

#include <stdio.h>
  
void delete_repeatedchar(char *a)
{
    if(a==NULL)
        return;
    char hash_table[256] = {0};
    char *p = a;
    while(*p != '\0')
        hash_table[*p++]=1;//注意这里，设为1标识这个字符出现过一次，为后面删除重复字符做准备  
    char *fast = a;
    char *slow = a;
    while(*fast != '\0')
    {  
        if(hash_table[*fast] == 0)//如果这个字符出现过，会将原来的1值变为0，所以代表这个字符曾经出现过，不能够赋值给*slow  
        {
            fast++;
        }
        else
        {
            hash_table[*fast]--;//如果第一次出现，则可直接赋值给*slow，并把1变为0  
            *slow++ = *fast++;  
        }
    }
    *slow = '\0';
}
  
int main()
{
    char a[] = "google!!!!!";
    printf("%s删除重复出现的字符后为:\n",a);
    delete_repeatedchar(a);
    printf("%s\n",a);
    return 0;
}
