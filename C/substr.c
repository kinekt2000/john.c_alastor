#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Удаление символа переноса строки из буфера ввода
void clean_buffer()
{
    int c;
    while((c = getchar()) != '\n');
}

int substr(char* str1, char* str2, int** result);

int main()
{
    int str1_len; // Размер подстроки
    int str2_len; // Размер строки в которой искать подстроку
    scanf("%i %i", &str1_len, &str2_len);
    clean_buffer();

    char* str1; 
    char* str2; 

    // Выделить память и считать строки
    str1 = malloc(str1_len+2);
    fgets(str1, str1_len+2, stdin);
    *strchr(str1,'\n') = 0;
    str2 = malloc(str2_len+2);
    fgets(str2, str2_len+2, stdin);
    *strchr(str2,'\n') = 0;

    int* result;
    int arr_len = substr(str1, str2, &result);
    int i = 0;
    for(i = 0; i < arr_len; i++)
        printf("%i ", result[i]);
}

// не изменяйте тип и количество аргументов этой функции
int substr(char* str1, char* str2, int** result)
{
    int size = 5;
    *result = malloc(size*sizeof(int));
    int i_of_result = 0;
    int i_of_str;

    for (i_of_str = 0; i_of_str < strlen(str2);){
        if (i_of_result != 0 && i_of_result % 5 == 0){     //  Условие, динамически
            size +=5;                                      //  увеличивающее размер массива,
            *result = realloc(*result, size*sizeof(int));  //  подающегося на выход
        }
        if (strstr(&str2[i_of_str], str1)){
            (*result)[i_of_result] = strstr(&str2[i_of_str], str1) - str2; // Индекс первого символа подстроки str1, входящей в строку str2
            i_of_str = strstr(&str2[i_of_str], str1) + strlen(str1) - 1 - str2; // Индекс последнего символа подстроки str1, входящей в строку str2
            i_of_result++; // Увеличение индекса массива, подающегося на выход, а так же количество элементов в этом массиве
        }
        else break;
    }
    return i_of_result;
}







