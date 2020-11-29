#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "atr.h"

#define SIZE		32

#define UP		65
#define DOWN		66
#define RIGHT		67
#define LEFT		68

#define BG B_BLACK
#define Lt B_WHITE

char loose_screen[SIZE][SIZE] =
			{{ BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
                     	 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,Lt,Lt,Lt,BG,BG,BG,BG,BG,Lt,BG,BG,BG,BG,BG,Lt,BG,Lt,BG,BG,BG,Lt,Lt,Lt,Lt,Lt,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,BG,Lt,BG,BG,BG,BG,BG,Lt,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,Lt,BG,Lt,BG,BG,BG,BG,Lt,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,BG,BG,BG,BG,Lt,BG,Lt,BG,BG,BG,Lt,BG,Lt,BG,Lt,BG,BG,Lt,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,Lt,BG,Lt,BG,BG,BG,Lt,Lt,BG,BG,BG,BG,BG },
                     	 { BG,BG,BG,Lt,BG,Lt,Lt,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,Lt,BG,Lt,BG,BG,Lt,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,Lt,Lt,Lt,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG },
			 { BG,BG,BG,BG,Lt,Lt,Lt,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,Lt,Lt,Lt,Lt,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
                         { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,Lt,Lt,Lt,BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,Lt,Lt,Lt,Lt,BG,BG,Lt,Lt,Lt,Lt,BG,BG,BG,BG },
                     	 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,Lt,Lt,BG,BG,BG,BG,Lt,Lt,Lt,Lt,BG,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,Lt,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,BG,BG,BG,Lt,BG,Lt,BG,BG,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,Lt,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,BG,BG,BG,Lt,BG,Lt,BG,BG,BG,BG,BG },
			 { BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG,BG,Lt,BG,BG,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,Lt,BG,BG,Lt,BG,BG,BG,BG },
			 { BG,BG,BG,BG,Lt,Lt,Lt,BG,BG,BG,BG,BG,Lt,BG,BG,BG,BG,Lt,Lt,Lt,Lt,Lt,BG,BG,Lt,BG,BG,BG,Lt,BG,BG,BG },
                     	 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG },
			 { BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG,BG }};

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
	struct termios _oldattr, _newattr;
	char ch = 0;

	tcgetattr(STDIN_FILENO, &_oldattr);
	_newattr = _oldattr;
	_newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &_newattr);

	int retval;

	FD_ZERO(&rds);
	FD_SET(0, &rds);
	tv.tv_sec = 0;
	tv.tv_usec = 60000;

	retval = select(1, &rds, NULL, NULL, &tv);
	putchar('\n');

	if (retval){
		ch = getchar();
		if (ch == 27){
			getchar();
			ch = getchar();
		}
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &_oldattr);

	return ch;
}


void exit_handler();
void redraw(char field[SIZE][SIZE]);
void draw_loose_screen();
int change_direction(snake *player);

void init_snake(snake *player);
void addSnake(char field[SIZE][SIZE], snake *player);
void remSnake(char field[SIZE][SIZE], snake *player);

int step(char field[SIZE][SIZE], snake *player, part *food);
void place_food(char field[SIZE][SIZE], part* food);

char gameover(snake *player);
char food_exists(part *food);

struct termios oldattr, newattr;
struct winsize ws;

int main(void){
	tcgetattr(STDIN_FILENO, &oldattr);

	signal(SIGINT, exit_handler);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	if (ws.ws_col < 66 || ws.ws_row < 37){
		printf(	"You should make your terminal bigger\n\n"
			"At least:\n"
			"66 sybols horizontal,\n"
			"37 symbols vertical.\n"
			"For best result open terminal as full window.\n");
		return 0;
	}

	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

	char field[SIZE][SIZE];
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			field[i][j] = B_GREEN;

	snake player;
	part food = {-1, -1};
	init_snake(&player);
	addSnake(field, &player);

	home();
	clrscr();
	redraw(field);
	visible_cursor();

	int exit;
	while(1){
		exit += change_direction(&player);

		exit += step(field, &player, &food);

		if(exit)break;

		gotoxy(1, SIZE+3);
		printf("pts - %d", player.size);

		if (!food_exists(&food))
			place_food(field, &food);

		redraw(field);
		//usleep(90000);
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	printf(ESC "[?25h");
	return 0;
}

void exit_handler(){
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	printf(ESC "[?25h");
	exit(0);
}

char food_exists(part *food){
	if (food->x == -1 || food->y == -1)
		return 0;
	return 1;
}

void place_food(char field[SIZE][SIZE],part *food){
	srand(time(NULL));

	int x = rand()%32 + 1;
	int y = rand()%32 + 1;

	if (field[y-1][x-1] != B_RED){
		field[y-1][x-1] = B_BLACK;
		food->x = x;
		food->y = y;
	}
}

void init_snake(snake *player){
	player->size = 2;

	player->body[0].x = 16;
	player->body[0].y = 16;
	player->body[1].x = 17;
	player->body[1].y = 16;

	player->direction = RIGHT;
}

void addSnake(char field[SIZE][SIZE], snake *player){
	for(int i = 0; i < player->size; i++)
		field[player->body[i].y - 1][player->body[i].x - 1] = B_RED;
}

void remSnake(char field[SIZE][SIZE], snake *player){
	for(int i = 0; i < player->size; i++)
		field[player->body[i].y - 1][player->body[i].x - 1] = B_GREEN;
}

int step(char field[SIZE][SIZE], snake *player, part *food){
	remSnake(field, player);

	for(int i = player->size - 1; i > 0; i--)
		player->body[i] = player->body[i - 1];

	switch (player->direction){
	case UP:
		player->body[0].y--;
		break;
	case DOWN:
		player->body[0].y++;
		break;
	case RIGHT:
		player->body[0].x++;
		break;
	case LEFT:
		player->body[0].x--;
		break;
	}

	if (player->body[0].x < 1) player->body[0].x = SIZE;
	if (player->body[0].x > SIZE) player->body[0].x = 1;
	if (player->body[0].y < 1) player->body[0].y = SIZE;
	if (player->body[0].y > SIZE) player->body[0].y = 1;

	addSnake(field, player);

	if(player->body[0].x == food->x && player->body[0].y == food->y){
		player->body[player->size] = player->body[player->size - 1];
		player->size++;
		food->x = -1;
		food->y = -1;
	}

	if (gameover(player)){
		draw_loose_screen();
		puts("You got nothing, You loosed! Good day sir!");
		tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
		return 1;
	}
	return 0;
}

char gameover(snake *player){
	for(int i = 1; i < player->size; i++)
		if (player->body[0].x == player->body[i].x && player->body[0].y == player->body[i].y)
			return 1;
	return 0;
}


void draw_loose_screen(){
	gotoxy(1, 1);
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			set_display_atr(BG);
			printf("  ");
		}
		putchar('\n');
	}

	gotoxy(1, 1);

	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			set_display_atr(loose_screen[i][j]);
			printf("  ");
		}
		putchar('\n');
		usleep(10000);
	}
	resetcolor();
	gotoxy(1, SIZE+4);
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

int change_direction(snake *player){
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
		return 1;
	}
	return 0;
}
