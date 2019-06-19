#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(){
    setlocale(LC_CTYPE, "");

    wprintf(L"Поместите требуемый для обработки текст в файл input.txt\n");
    wprintf(L"Если текст введен в требуемый файл, для продолжения нажмите введите \"y\" \n");
    wprintf(L"Если хотите выйти из программы, нажмите enter или ctrl+c\n");
    for(;;){
        wchar_t exitC = fgetwc(stdin);
        if (exitC == L'\n') return 0;
        ungetwc(exitC, stdin);
        wchar_t f = fgetwc(stdin);
        wchar_t inpC = fgetwc(stdin);
        if (inpC == L'\n'){
            if (f == L'y') break;
            else continue;
        }
        else{
            do
                inpC = fgetwc(stdin);
            while (inpC != L'\n');
            wprintf(L"Wrong input\n");
            continue;
        }
    }

        wprintf(L"Вам предложено меню, выберите требуемую функцию нажатием вводом соответствующей цифры\n");
        wprintf(L"0: \n");
        wprintf(L"1: \n");
        wprintf(L"2: \n");
        wprintf(L"3: \n");
        wprintf(L"4: \n");
        wprintf(L"5: \n");
        wprintf(L"6: \n");
        wprintf(L"7: \n");
        wprintf(L"Для выхода из программы нажмите enter или ctrl+c\n\n");


    for(;;){

        int f;
        wchar_t exitC = fgetwc(stdin);
        if (exitC == L'\n') break;
        ungetwc(exitC, stdin);
        wscanf(L"%d", &f);
        wchar_t inpC = fgetwc(stdin);
        if (inpC == L'\n'){

            switch (f){
                case 0: wprintf(L">>> 0\n"); break;
                case 1: wprintf(L">>> 1\n"); break;
                case 2: wprintf(L">>> 2\n"); break;
                case 3: wprintf(L">>> 3\n"); break;
                case 4: wprintf(L">>> 4\n"); break;
                case 5: wprintf(L">>> 5\n"); break;
                case 6: wprintf(L">>> 6\n"); break;
                case 7: wprintf(L">>> 7\n"); break;
                default: wprintf(L"Wrong function\n");  break;
            }

        }
        else{
            do
                inpC = fgetwc(stdin);
            while (inpC != L'\n');
            wprintf(L"Wrong input\n");
            continue;
        }
    }
    return 0;
}
