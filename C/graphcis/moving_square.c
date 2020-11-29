#include "atr.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

#define BORDER 32

#define LEFT 68
#define UP 65
#define RIGHT 67
#define DOWN 66


/*int getch(void){
	return fgetc(stdin);
}*/


/*int kbhit(){
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &fds);
}


void nonblock(int state){
	struct termios ttystate;
	if (state == NB_ENABLE){
		ttystate.c_lflag &= ~ICANON;
		ttystate.c_cc[VMIN] = 1;
	}
	else if (state == NB_DISABLE){
		ttystate.c_flag |= ICANON;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}*/




typedef struct{
        int x;
        int y;
}cursor;


void fill_field();
void move(cursor* pos, int direction);
void setpixel(int x, int y);


void delay(int m_secs){
	clock_t start_time = clock();
	while(clock() < start_time + m_secs);
}

int getch(void){
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}


int main(void){
	cursor pos = {16, 16};

	home();
	clrscr();
	fill_field();

	gotoxy(pos.x*2, pos.y);
	set_display_atr(B_RED);
	putchar(' ');
	gotoxy(pos.x*2-1, pos.y);
	putchar(' ');

	gotoxy(1, 36);
	resetcolor();

	char i_input;
	//int direction;

	for(;1;){
		gotoxy(1, 36);
		i_input = getch();
		move(&pos, i_input);
		gotoxy(1, 36);
	}

	gotoxy(1, 36);
	return 0;
}


void setpixel(int x, int y){
	gotoxy(x*2, y);
	putchar(' ');
	gotoxy(x*2-1, y);
	putchar(' ');
	gotoxy(1, BORDER + 5);
}


void fill_field(){
	home();
	set_display_atr(B_GREEN);
	for(int i = 0; i < 32; i++){
		for(int j = 0; j < 64; j++)
			putchar(' ');
		putchar('\n');
	}
	resetcolor();
}

void move(cursor *pos, int direction){

	switch (direction){
	case LEFT:	//left
        	set_display_atr(B_GREEN);
        	setpixel(pos->x, pos->y);

        	set_display_atr(B_RED);
		pos->x--;
		if (pos->x == 0) pos->x = 32;
		setpixel(pos->x, pos->y);
		break;
	case RIGHT:	//right
        	set_display_atr(B_GREEN);
		setpixel(pos->x, pos->y);

        	set_display_atr(B_RED);
		pos->x++;
		if (pos->x == 33) pos->x = 1;
		setpixel(pos->x, pos->y);
		break;
	case UP:	//up
        	set_display_atr(B_GREEN);
        	setpixel(pos->x, pos->y);

        	set_display_atr(B_RED);
		pos->y--;
		if (pos->y == 0) pos->y = 32;
		setpixel(pos->x, pos->y);
		break;
	case DOWN:	//down
        	set_display_atr(B_GREEN);
        	setpixel(pos->x, pos->y);

        	set_display_atr(B_RED);
		pos->y++;
		if (pos->y == 33) pos->y = 1;
		setpixel(pos->x, pos->y);
		break;
	}
	resetcolor();
}
