#include "text.h"
#include "sentence.h"


int main(){
    struct Text input;
    readText(&input);
    printText(input);
    return 0;
}
