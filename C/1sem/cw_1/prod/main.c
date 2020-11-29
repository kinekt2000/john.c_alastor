#include "sentence.h"
#include "text.h"

void menu(){
    wprintf(L"\nВам предложено меню, выберите требуемую функцию нажатием вводом соответствующей цифры\n");
    wprintf(L"0: Повтор меню\n");
    wprintf(L"1: Вывод текста\n");
    wprintf(L"2: Формат. Удаление предложений в которых есть слова начинающиеся с маленькой буквы\n");
    wprintf(L"3: Формат. Сортировка слов в предложениях по количеству гласных букв\n");
    wprintf(L"4: Формат. Вывод повторяющихся слов, а также количество повторений\n");
    wprintf(L"5: Формат. Составление общей маски из слов в предложении\n");
    wprintf(L"6: Очистка формата\n");
    wprintf(L"7: Вывод формата\n");
    wprintf(L"Для выхода из программы нажмите enter или ctrl+c\n\n");
}

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
    putwc(L'\n', stdout);

        
    struct Text input;
    struct Text format;
    int formatInd = 0;
    readText(&input);

    menu();

    
    for(;;){

        int f;
        wchar_t exitC = fgetwc(stdin);
        if (exitC == L'\n') break;
        ungetwc(exitC, stdin);
        wscanf(L"%d", &f);
        wchar_t inpC = fgetwc(stdin);
        if (inpC == L'\n'){

            switch (f){
                case 0:
                    menu();
                    break;

                case 1:
                    printText(input);
                    putwc(L'\n', stdout);
                    break;

                case 2:
                    if (formatInd) { wprintf(L"Требуется очистка формата\n"); putwc(L'\n', stdout); }
                    else{
                        textCaps(input, &format);
                        formatInd = 1;
                        putwc(L'\n', stdout);
                    }
                    break;

                case 3:
                    if (formatInd) { wprintf(L"Требуется очистка формата\n"); putwc(L'\n', stdout); }
                    else{
                        textVowSort(input, &format);
                        formatInd = 1;
                        putwc(L'\n', stdout);
                    }
                    break;

                case 4:
                    if (formatInd) { wprintf(L"Требуется очистка формата\n"); putwc(L'\n', stdout); }
                    else{
                        textWordsCount(input, &format);
                        formatInd = 1;
                        putwc(L'\n', stdout);
                    }
                    break;

                case 5:
                    if (formatInd) { wprintf(L"Требуется очистка формата\n"); putwc(L'\n', stdout); }
                    else{
                        textPattern(input, &format);
                        formatInd = 1;
                        putwc(L'\n', stdout);
                    }
                    break;

                case 6: 
                    if (formatInd){
                        cleanText(format);
                        wprintf(L"Формат очищен\n");
                        formatInd = 0;
                        putwc(L'\n', stdout);
                    }
                    else { wprintf(L"Формат пуст\n"); putwc(L'\n', stdout); }
                    break;

                case 7:
                    if (!formatInd) { wprintf(L"Формат пуст\n"); putwc(L'\n', stdout); } 
                    else{                    
                        printText(format);
                        putwc(L'\n', stdout);
                    }
                    break;

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
