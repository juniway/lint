#include <iostream>
#include <cassert>
using namespace std;

char* diffstring(char* s1, char* s2){
    assert(s1 != nullptr && s2 != nullptr);
    char hashTable[255] = { 0 };

    int sz1 = 0, sz2 = 0;
    char* s1_mover = s1;


    while (*s2 != '\0' && *s1_mover != '\0'){
        hashTable[*s2]++;
        s2++;
        sz1++;
        sz2++;
    }
    if(sz1 < sz2){
        printf("len of s1 less than len of s2.\n");
        return nullptr;
    }

    char* new_str = new char[sz1 - sz2 + 1];
    char* cur = new_str;

    while (*s1 != '\0'){
        if (hashTable[*s1] == 1){
            s1++;
        }
        else{
            *cur++ = *s1++;
        }
    }
    return new_str;


}


int main(){
    char* str1 = "They are students";
    char* str2 = "aeiou";
    char* diff_str = diffstring(str1, str2);
    cout << diff_str << endl;
    return 0;
}