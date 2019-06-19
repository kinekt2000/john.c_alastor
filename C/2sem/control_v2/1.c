#include <stdio.h>
#include <math.h>

/*int main(){
	double inp;
	scanf("%lf", &inp);
	int full;
	double fract;
	if (inp > 0)
		full = floor(inp);
	else
		full = ceil(inp);
	fract = inp - full;
	printf("%d\n%lg\n", full, fract);
	return 0;
}*/


int main(){
	double inp;
	scanf("%lf", &inp);
	double full;
	double fract = modf(inp, &full);
	printf("%d\n%lg\n", (int)full, fract);
	return 0;
}
