#include "text.h"
#include "sentence.h"


int main(){
    char** text;
    readText(&text);
    int f;
    scanf("%d", &f);
    formatText(&text, f);
    printf("%d\n", printText(text));
    return 0;
}
