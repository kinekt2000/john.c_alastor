#include "input.h"


int main(){
    char** text;
    int sizeText = readText(&text);
    for(int i = 0; text[i]; i++) printf("%s\n", text[i]);
    return 0;
}
