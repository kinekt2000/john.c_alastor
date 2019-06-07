#include "text.h"
#include "sentence.h"


int main(){
    struct Text input;
    struct Text format;
    readText(&input);
    textCaps(input, &format);
    printText(input);
    puts("");
    printText(format);
    //printf("%d\n", input.sizeText);
    return 0;
}
