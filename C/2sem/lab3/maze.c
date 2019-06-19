#include <stdio.h>
#include <stdlib.h>

void printMaze(int** maze, int h, int w);
void isexit(int**, int, int);

int main(){
        int size_x, size_y;
        scanf("%d %d", &size_y, &size_x);
        size_y += 2;
        size_x += 2;
        int** maze = (int**)calloc(size_y, sizeof(int*));
        for (int i = 0; i < size_y; i++){
                maze[i] = (int*)calloc(size_x, sizeof(int));
                if (i == 0 || i == size_y - 1){
                        for(int j = 0; j < size_x; j++) maze[i][j] = 1;
                        continue;
                }
                for(int j = 0; j < size_x; j++){
                        if (j == 0 || j == size_x - 1){
                                maze[i][j] = 1;
                                continue;
                        }
                        scanf("%d", &(maze[i][j]));
                }
        }
        printf("\n");
        isexit(maze, 1, 1);

        if (maze[size_y - 2][size_x - 2] == 2) printf("exists\n");
        else printf("doesn't exist\n");

        //printMaze(maze, size_y, size_x);

        for(int i = 0;  i < size_y; i++) free(maze[i]);
        free(maze);
        return 0;
}

void isexit(int** maze, int y, int x){
        if (maze[y][x] == 1 || maze[y][x] == 2) return;
        maze[y][x] = 2;
        isexit(maze, y-1, x); // north
        isexit(maze, y, x+1); // east
        isexit(maze, y+1, x); // south
        isexit(maze, y, x-1); // west
        return;
}


void printMaze(int** maze, int h, int w){
        for (int i = 0; i < h; i++){
                for (int j = 0; j < w; j++){
                        printf("%d ", maze[i][j]);
                }
                printf("\n");
        }
}

