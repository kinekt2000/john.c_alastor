#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define END_SENTENCE "Dragon flew away!"
#define REMOVE_SYMB '?'
#define MEM_BLOCK_SIZE 50

int is_sentence_end_symbol(char c){

    return (c == '.' || c == ';' || c == '?');

}

void add_sentence(char*** text, char* sentence, int* sentences_count, int* max_text_len){

    *sentences_count += 1;

    if (*sentences_count > *max_text_len){

        *max_text_len += MEM_BLOCK_SIZE;

        char** tmp = realloc(*text, (*max_text_len)*sizeof(char*));

        if(tmp){
            *text = tmp;
        } else{
            printf("\t\tError in allocate memory for text");
        }

    }

    (*text)[*sentences_count-1] = sentence;

}

void add_symbol(char** sentence, char symbol, int* sent_len, int* max_sent_len){

    *sent_len += 1;

    if (*sent_len > *max_sent_len){

        *max_sent_len += MEM_BLOCK_SIZE;

        char* tmp = realloc(*sentence, (*max_sent_len)*sizeof(char));
        if (tmp){
            *sentence = tmp;
        } else{
            printf("\t\tError in allocate memory for sentence");
        }

    }


    (*sentence)[*sent_len-2] = symbol;
    (*sentence)[*sent_len-1] = '\0';


}

char** read_text(int* text_len){

    char** text = NULL;
    *text_len = 0;

    int max_text_len = 0;

    char* now_sent = calloc(1, sizeof(char));
    int now_sent_len = 1;
    int max_sent_len = 1;
    char now_symbol;

    int is_sent_began = 0;


    while (strcmp(now_sent, END_SENTENCE)){

        scanf("%c", &now_symbol);

        if (isblank(now_symbol) && !is_sent_began){
            continue;
        } else{

            is_sent_began = 1;

            add_symbol(&now_sent, now_symbol, &now_sent_len, &max_sent_len);

            if (is_sentence_end_symbol(now_symbol)){

                char* tmp = realloc(now_sent, now_sent_len*sizeof(char));
                if (tmp){
                    now_sent = tmp;
                } else{
                    printf("Error in realloc now_sent to now_sent_len");
                }

                add_sentence(&text, now_sent, text_len, &max_text_len);

                now_sent = calloc(1, sizeof(char));
                now_sent_len = 1;
                max_sent_len = 1;

                is_sent_began = 0;

            }

        }

    }

    char** tmp = realloc(text, (*text_len)*sizeof(char*));

    if(tmp){
        text = tmp;
    } else{
        printf("Error in realloc text to text_len");
    }

    return text;

}

void remove_sent(char*** text, int* text_len, int index){

    for(int i=index+1; i<*text_len; i++){
        (*text)[i-1] = (*text)[i];
    }

    *text_len -= 1;
    char** tmp = realloc(*text, *text_len*sizeof(char*));

    if (tmp){
        *text = tmp;
    } else{
        printf("Error to realloc memory in remove_sent func\n");
    }

}

void remove_sents_with_simb(char*** text, int* text_len){

    for (int i=0; i<*text_len;){

        int now_sent_len = strlen((*text)[i]);
        if ((*text)[i][now_sent_len-1] == REMOVE_SYMB){
            remove_sent(text, text_len, i);
            i--;
        }

        i++;

    }

}

int main() {

    int text_len;

    char** text = read_text(&text_len);

    int text_len_before_format = text_len;
    remove_sents_with_simb(&text, &text_len);
    int text_len_after_format = text_len;

    for (int i=0; i<text_len; i++){
        printf("%s\n", text[i]);
    }

    printf(END_SENTENCE"\n");

    printf("Количество предложений до %d и количество предложений после %d\n", text_len_before_format, text_len_after_format);

    for (int i=0; i<text_len; i++){
        free(text[i]);
    }
    free(text);

    return 0;
}
