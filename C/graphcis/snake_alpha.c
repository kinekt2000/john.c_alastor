#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "atr.h"

#define NB_DISABLE	0
#define NB_ENABLE	1

#define SIZE		32

#define UP		65
#define DOWN		66
#define RIGHT		67
#define LEFT		68

typedef struct pixel{
	int x;
	int y;
	int direction;
}pixel;

typedef struct part{
	int x;
	int y;
}part;

typedef struct snake{
	part body[SIZE*SIZE];
	int size;
	int direction;
}snake;

char instant_input(){
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
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	retval = select(1, &rds, NULL, NULL, &tv);
	putchar('\n');

	if (retval){
		ch = getchar();
		if (ch == 27){
			getchar();
			ch = getchar();
		}
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

	return ch;
}


/*int kbhit(){
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	int res = select(1, &fds, NULL, NULL, &tv);
	printf("%d ", res);
	return res;
	//return FD_ISSET(STDIN_FILENO+1, &fds);
}


int getch(){
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}*/

void addToField(char field[SIZE][SIZE], pixel *player);
void remFromField(char field[SIZE][SIZE], pixel *player);

void redraw(char field[SIZE][SIZE]);
void change_direction(pixel *player);
void movePlayer(pixel *player);

/*void init_snake(snake *player);
void addSnake(char field[SIZE][SIZE], snake *player);
void remSnake(char field[SIZE][SIZE], snake *player);
void moveSnake(snake *player);*/


struct termios oldattr, newattr;

int main(void){
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

	char field[SIZE][SIZE];
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			field[i][j] = B_GREEN;

	pixel player = {16, 16, RIGHT};
	addToField(field, &player);

	home();
	clrscr();
	redraw(field);
	char ch;

	for(int i = 0;1; i++){
		change_direction(&player);

		remFromField(field, &player);
		movePlayer(&player);
		addToField(field, &player);

		redraw(field);
		usleep(100000);
	}


	return 0;
}

void addToField(char field[SIZE][SIZE], pixel *player){
	field[player->y - 1][player->x - 1] = B_RED;
}

void remFromField(char field[SIZE][SIZE], pixel *player){
	field[player->y - 1][player->x - 1] = B_GREEN;
}

void movePlayer(pixel *player){
	switch (player->direction){
	case UP:
		player->y--;
		break;
	case DOWN:
		player->y++;
		break;
	case RIGHT:
		player->x++;
		break;
	case LEFT:
		player->x--;
		break;
	}

	if (player->x < 1) player->x = 32;
	if (player->x > 32) player->x = 1;
	if (player->y < 1) player->y = 32;
	if (player->y > 32) player->y = 1;
}

void redraw(char field[SIZE][SIZE]){
	gotoxy(1,1);
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			set_display_atr(field[i][j]);
			printf("  ");
		}
		putchar('\n');
	}
	resetcolor();
	gotoxy(1, SIZE+4);
}

void change_direction(pixel *player){
	char ch = instant_input();
	switch (ch){
	case UP:
		if (player->direction != DOWN)
			player->direction = UP;
		break;
	case DOWN:
		if (player->direction != UP)
			player->direction = DOWN;
		break;
	case LEFT:
		if (player->direction != RIGHT)
			player->direction = LEFT;
		break;
	case RIGHT:
		if (player->direction != LEFT)
			player->direction = RIGHT;
		break;
	case 113:
		tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
		exit(0);
	}
}
