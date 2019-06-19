#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* merge(char* str1, char* str2);

int main()
{
    int str1_len;
    int str2_len;
    scanf("%d %d\n", &str1_len, &str2_len);
    char* str1 = malloc(str1_len+2);
    char* str2 = malloc(str2_len+2);
    fgets(str1, str1_len+2, stdin);
    *strchr(str1, '\n') = 0;
    fgets(str2, str2_len+2, stdin);
    *strchr(str2, '\n') = 0;

    printf("%s\n", merge(str1, str2));
}

char* merge(char* str1, char* str2)
{
    int str1_len = strlen(str1);
    int str2_len = strlen(str2);
    if (str1_len == str2_len){
        char* out = (char*) malloc(str1_len+str2_len+1);
        for (int i = 0; i < str1_len+str2_len+1 ; i++)
            out[i] = (i%2) ? str2[i/2] : str1[i/2];
        out[str1_len+str2_len+1] = 0;
        return out;
    }
    else if (str1_len > str2_len){
        char* out = (char*) malloc(str1_len+str2_len+1);
        for (int i = 0; i < str2_len*2; i++)
            out[i] = (i%2) ? str2[i/2] : str1[i/2];
        strcat(out, &str1[str2_len]);
        out[str1_len+str2_len+1] = 0;
        return out;
    }
    else{
        char* out = (char*) malloc(str1_len+str2_len+1);
        for (int i = 0; i < str1_len*2; i++)
            out[i] = (i%2) ? str2[i/2] : str1[i/2];
        strcat(out, &str2[str1_len]);
        out[str1_len+str2_len+1] = 0;
        return out;
    }
}
