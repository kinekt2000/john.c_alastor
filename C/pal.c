#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_palindrome(char* word);

int main()
{
    int str_len;
    scanf("%d\n", &str_len);
    char* str = malloc(str_len+2);
    fgets(str, str_len+2, stdin);
    *strchr(str, '\n') = 0;
    is_palindrome(str) ? printf("true") : printf("false");
    return 0;
}

// Дописать функцию
int is_palindrome(char* word)
{
    char *ptr_start = word; // адрес первого символа
    char *ptr_end = strchr(word, 0) - 1; // адрес последнего символа

    while(ptr_end - ptr_start > 0)
    {
        printf("%ld\n", ptr_end-ptr_start);
        if (*ptr_end == *ptr_start){
            ptr_end --;
            ptr_start ++;
        }
        else return 0;
    } 

    return 1;
}
