#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "atr.h"


#define home()			printf(ESC "[H")
#define clrscr()		printf(ESC "[2J")
#define gotoxy(x, y)		printf(ESC "[%d;%dH", y, x);
#define visible_cursor()	printf(ESC "[?251")

#define resetcolor()		printf(ESC "[0m")
#define set_display_atrib(clr)	printf(ESC "[%dm", clr)

void draw_frame();
void time_date(struct tm* tm_info);

int main(void){
	home();
	clrscr();
	draw_frame();

	time_t timer;
	struct tm *tm_info;

	for(int i = 0;1;i++){
		set_display_atrib(i%8 + F_BLACK);
		set_display_atrib(7 - i%8 + B_BLACK);

		time(&timer);
		tm_info = localtime(&timer);
		time_date(tm_info);
		resetcolor();

		gotoxy(1,10);
		fflush(stdout);
		usleep(1000000);
	}

	return 0;
}


void draw_frame(){
	home();
	set_display_atrib(B_BLUE);

	//	           11
	//	 123456789012
	puts(	"┌──────────┐\n"   //1
		"│          │\n"   //2
		"│          │\n"   //3
		"│          │\n"   //4
		"│          │\n"   //5
		"└──────────┘");   //6
	resetcolor();
}


void time_date(struct tm* tm_info){
	char buffer[12];
	//set_display_atrib(BRIGHT);
	//set_display_atrib(B_BLUE);
	strftime(buffer, 12, "%d.%m.%y", tm_info);
	gotoxy(3, 3);
	puts(buffer);
	strftime(buffer, 10, "%H:%M:%S", tm_info);
	gotoxy(3, 4);
	puts(buffer);
	resetcolor();
}
