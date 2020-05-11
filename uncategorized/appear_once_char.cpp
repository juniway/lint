Questoin:
This was a Google interview puzzle.
The problem is to find the first element in an array that occurs only once.
For example, abaaacdgadgf is given. We need to output b.

Analysis:
The simple solution seems to be to first count every element using a hashtable,
and then loop through again to get the first element. It will use 2 loops.

Is it possible to get the result only use 1 loop?

Why not use a heap based data structure such as a minimum priority queue.
As you read each character from the string, add it to the queue with a priority
based on the location in the string and the number of occurrences so far.
You could modify the queue to add priorities on collision so that the priority of a
character is the sum of the number appearances of that character.
At the end of the loop, the first element in the queue will be the least frequent
character in the string and if there are multiple characters with a count == 1,
the first element was the first unique character added to the queue.

The hash table points to items in a linked list. When adding an item the hashtable entry
is created and the pointer added to the tail of the list. When a duplicate is found then the item can be removed from the list.
The first element to occur only once will be the first item in the list.
This code is a little untidy because most of the code is linked list implementation.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node{
    char data;
    struct Node* previous;
    struct Node* next;
} ;

char firstCharOccursOnce(const char* s) {
    char ret;
    Node* head;
    Node* tail;
    Node* table[26] = {NULL};
    Node* cur;
    int i;

    head = new Node();
    tail = new Node();

    head->next = tail;
    tail->previous = head;
    tail->data = '\0'; /* If all characters are repeated then return NULL character */

    for (; *s != '\0'; s++) {
        cur = table[*s - 'a'];

        if (cur == NULL) {
            // Item hasn't been seen before

            cur = new Node();
            cur->data = *s;

            /* Add it to the end of the list */
            tail->previous->next = cur;
            cur->previous = tail->previous;
            tail->previous = cur;
            cur->next = tail;

            /* Add it to the table */
            table[*s] = cur;
        }
        else if (cur->next == NULL) {
            /* Seen it before, but already removed */ continue;
        }
        else {
            /* Seen it before, remove from list */
            cur->previous->next = cur->next;
            cur->next->previous = cur->previous;

            cur->next = NULL;
            cur->previous = NULL;
        }
    }

    ret = head->next->data;

    for (i = 0; i < 26; i++) {
        free(table[i]);
    }

    free(head);
    free(tail);

    return ret;
}

char find(const char *str) {
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

int main(int argc, char const *argv[]){
    char result = firstCharThatOccursOnce("abaaacdgadgf");
    printf("'%c' (%i)\n", result, result);

    return 0;
}