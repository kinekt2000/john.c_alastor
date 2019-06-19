#include "text.h"
#include "sentence.h"


int main(){
    struct Text input;
    struct Text format;
    readText(&input);
    printText(input);
    return 0;
}
