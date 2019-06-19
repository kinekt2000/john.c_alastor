#include "atr.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

#define NB_DISABLE 0
#define NB_ENABLE 1

#define BORDER 32

#define LEFT 68
#define UP 65
#define RIGHT 67
#define DOWN 66
#define NONE 0


int getch(void){
	return fgetc(stdin);
}


int kbhit(){
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
		ttystate.c_lflag |= ICANON;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}


typedef struct cell{
	int x;
	int y;
}cell;

typedef struct snake{
	cell body[BORDER*BORDER];
	int size;
	int direction;
}snake;


void standart_settings(snake *snk){
	snk->body[0].x = 1;
	snk->body[0].y = 2;
	snk->body[1].x = 1;
	snk->body[1].y = 1;

	snk->size = 2;
	snk->direction = RIGHT;
}


void init_field(char field[BORDER][BORDER]){
	for(int i = 0; i < BORDER; i++)
		for(int j = 0; j < BORDER; j++)
			field[i][j] = B_GREEN;
}


void draw_field(char field[BORDER][BORDER]){
	home();
	for (int i = 0; i < BORDER; i++){
		for(int j = 0; j < BORDER; j++){
			if (field[i][j] == B_GREEN)
				set_display_atr(B_GREEN);
			else
				set_display_atr(B_RED);
			putchar(' ');
			putchar(' ');
		}
		putchar('\n');
	}
	resetcolor();
}


void clear_snake(char field[BORDER][BORDER], snake *player){
	for(int i = 0; i < player->size; i++){
		field[player->body[i].y][player->body[i].x] = B_GREEN;
	}
}


void draw_snake(char field[BORDER][BORDER], snake *player){
	//printf("%d : %d %d\n", player->size, player->body[0].x, player->body[0].y);
	//field[3][3] = B_RED;

	for(int i = 0; i < player->size; i++){
		field[player->body[i].y][player->body[i].x] = B_RED;
	}
}


void check_coordinates(snake *player){
	if (player->body[0].x > BORDER) player->body[0].x = 0;
	if (player->body[0].x < 0) player->body[0].x = BORDER - 1;
	if (player->body[0].y > BORDER) player->body[0].y = 0;
	if (player->body[0].x < 0) player->body[0].y = BORDER - 1;
}


void change_direction(snake *player){
	char  symbol = getch();
	printf("%c\n", symbol);
	switch (symbol){
	case 'w':
		if (player->direction != UP)
			player->direction = UP;
		break;
	case 'a':
		if (player->direction != LEFT)
			player->direction = LEFT;
		break;
	case 's':
		if (player->direction != DOWN)
			player->direction = DOWN;
		break;
	case 'd':
		if (player->direction != RIGHT)
			player->direction = RIGHT;
		break;
	default: break;
	}
}


void next_step(char field[BORDER][BORDER], snake *player){
	clear_snake(field, player);

	for(int i = player->size - 1; i >= 1; i--){
		player->body[i].x = player->body[i - 1].x;
		player->body[i].y = player->body[i - 1].y;
	}

	int change_x = 0;
	int change_y = 0;
	if	(player->direction == RIGHT)
		change_x++;
	else if (player->direction == LEFT)
		change_x--;
	else if (player->direction == UP)
		change_y--;
	else if (player->direction == DOWN)
		change_y++;

	player->body[0].x += change_x;
	player->body[0].y += change_y;

	check_coordinates(player);
	draw_snake(field, player);
}


int main(){
	char field[BORDER][BORDER];
	init_field(field);

	snake player;
	standart_settings(&player);
	draw_snake(field, &player);

	draw_field(field);

	gotoxy(1, BORDER + 4);
	while(1){
		int a = kbhit();
		gotoxy(1, BORDER + 5);
		printf("%d\n", a);
		if(a != 0)
			change_direction(&player);

		next_step(field, &player);
		draw_field(field);
		clrscr();
		usleep(200000);
	}
}



