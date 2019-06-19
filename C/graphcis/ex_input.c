#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include "snake.c"

int main(){
	fd_set rds;
	struct timeval tv;
	struct termios oldattr, newattr;
	char ch = 0;

	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

	int retval;

	FD_ZERO(&rds);
	FD_SET(0, &rds);
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	retval = select(1, &rds, NULL, NULL, &tv);
	putchar('\n');

	if (retval){
		ch = getchar();
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

	if (ch)
		putchar(ch);
	else
		puts("no data");
	return 0;
}
