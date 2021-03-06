#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP "Dragon flew away!"  // Стоп-фраза

void processSentence(char** sentence);  // Обработка предложения
int processWord(char* word);            // Обработка слова

int main(){
    int memText = 0;
    char** text = (char**)malloc(sizeof(char*));
    char* buffer = (char*)malloc(2*sizeof(char));
    char inpC;

		// Ввод текста
    int sizeText;
    for(sizeText = 0; strcmp(buffer, STOP); sizeText++){  // Ввод текста, до тех пор, пока введенное предложение не станет равно стоп-фразе
        free(buffer);   // Очистка буфера

		// Увеличение памяти, в которой хранятся адреса предложений,
		// по мере ее заполнения
        if (sizeText % 5 == 0){ 
            memText += 5;
            text = (char**)realloc(text, memText*sizeof(char*));
        }

        do
            inpC = fgetc(stdin);
        while(inpC == ' ' || inpC == '\t' || inpC == '\n');


		// Ввод предложения
        int memString = 10;
        text[sizeText] = (char*)malloc((memString+1)*sizeof(char));
        *(text[sizeText]) = inpC;
        int sizeString;
        for(sizeString = 1; inpC != '.' && inpC != ';' && inpC != '?'; sizeString++){
		// Увеличение памяти, в которой хранится строка,
		// по мере ее считывания
            if (sizeString % 10 == 0){
                memString += 10;
                text[sizeText] = (char*)realloc(text[sizeText], (memString+1)*sizeof(char));
            }

		// Пропуск пустых символов
            inpC = fgetc(stdin);
            if (inpC == '\n') inpC = ' ';
		// Считывание очередного символа строки
            text[sizeText][sizeString] = inpC;
            text[sizeText][sizeString+1] = 0;
		// Выход из цикла, если предложение приняло вид стоп-фразы
            if (strcmp(text[sizeText], STOP) == 0) break;
        }
		// Выделение памяти для буфера, размером с текущую строку
        buffer = (char*)malloc((strlen(text[sizeText])+1)*sizeof(char));
		// Копирование текущей строки в буфер
        strcpy(buffer, text[sizeText]);
    }

		// Форматирование и вывод
    int newSizeText = 0;
    for(int i = 0; i < sizeText; i++){
        processSentence(&(text[i]));
        if (*text[i] == 0) { free(text[i]); continue;}
        printf("%s\n", text[i]);
        free(text[i]);
        newSizeText++;
    }

    free(text);	// Очистка памяти выделенной под адреса с предложениями
    printf("Количество предложений до %d и количество предложений после %d\n", sizeText-1, newSizeText-1);
    return 0;
}

int processWord(char* word){
    int identifier = 0;
    int len = strlen(word);
    int leftPointer;	// Индекс первой буквы справа
    for(leftPointer = 0; word[leftPointer] >= '0' && word[leftPointer] <= '9' && leftPointer != len - 1; leftPointer++);
    int rightPointer;	// Индекс первой буквы слева
    for(rightPointer = len - 1; word[rightPointer] >= '0' && word[rightPointer] <= '9' && rightPointer != 0; rightPointer--);

    if (rightPointer - leftPointer > 1)
        for(int i = leftPointer; i <= rightPointer; i++)
            if (word[i] >= '0' && word[i] <= '9')
                identifier = 1;
    if (identifier) return 1;
    else return 0;
}

 
void processSentence(char** sentence){
    char buffer[strlen(*sentence)+1];
    strcpy(buffer, *sentence);
    int identifier = 0;
    char* word = strtok(buffer, " ,.;?");
    for(int i = 0; word; i++){
        identifier += processWord(word);
        word = strtok(NULL, " ,.;?");
    }
    if (identifier) **sentence = 0;
}  
