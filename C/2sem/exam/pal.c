#include <stdio.h>
#include <string.h>

int main(){
	char str[202];
	fgets(str, 201, stdin);
	str[strlen(str) - 1] = 0;
	char check = 0;

	for(int i = 0; i < strlen(str)>>1; i++)
		if (str[i] != str[strlen(str) - 1 - i])
			check++;

	if(check)
		puts("NO");
	else
		puts("YES");
	return 0;
}
