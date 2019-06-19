#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
	char s[200];
	fgets(s, 200, stdin);
	s[strlen(s) - 1] = 0;
	int i, j;
	i = j = 0;
	for(; i <= strlen(s); i++)
		if (!isupper(s[i])){
			s[j] = s[i];
			j++;
		}

	puts(s);
	return 0;
}
