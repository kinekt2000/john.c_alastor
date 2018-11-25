#include <stdlib.h>
#include <stdio.h>

#ifndef STOP
#define STOP "The End!"
#endif

int readText(char*** text);
int printText(char** text);

	// Format text
void formatText(char*** text, int f);
int textCapitalMissing(char*** text);
