#include <stdio.h>
#include <stdlib.h>

int**  createMatrix(int h, int w);
void printMatrix(int** matrix, int h, int w);
void freeMatrix(int** matrix, int h);


void fill(int** matrix, int y, int x, int* sq);


int main(){
	int height, width;
	scanf("%d %d", &height, &width);
	height += 2;
        width += 2;
	int** matrix = createMatrix(height, width);
	printMatrix(matrix, height, width);
	printf("\n");
	/*int square = 0;
	fill(matrix, 2, 2, &square);
	printf("%d\n", square);
	printMatrix(matrix, height, width);*/

	int maxSquare = 0;
	int square;
	for(int i = 1; i < height; i++){
		for(int j = 0; j < width; j++){
			square = 0;
			if (matrix[i][j] == 1)
				fill(matrix, i, j, &square);
			if (square > maxSquare)
				maxSquare = square;
		}
	}
	printf("%d\n", maxSquare);

	freeMatrix(matrix, height);
	return 0;
}


int** createMatrix(int h, int w){
	int** matrix = (int**)malloc(h*sizeof(int*));
	for (int i = 0; i < h; i++){
		matrix[i] = (int*)malloc(w*sizeof(int));
                if (i == 0 || i == h - 1){
                        for(int j = 0; j < w; j++) matrix[i][j] = 0;
                        continue;
                }
                for(int j = 0; j < w; j++){
                        if (j == 0 || j == w - 1){
                                matrix[i][j] = 0;
                                continue;
                        }
                        scanf("%d", &(matrix[i][j]));
                }
        }
	return matrix;
}


void printMatrix(int** matrix, int h, int w){
	for (int i = 0; i < h; i++){
                for (int j = 0; j < w; j++){
                        printf("%d ", matrix[i][j]);
                }
                printf("\n");
        }
}


void freeMatrix(int** matrix, int h){
	for(int i = 0; i < h; i++) free(matrix[i]);
	free(matrix);
}


void fill(int** matrix, int y, int x, int* sq){
	if (matrix[y][x] == 0 || matrix[y][x] == 2) return;
        matrix[y][x] = 2;
	(*sq)++;
        fill(matrix, y-1, x, sq); // north
        fill(matrix, y, x+1, sq); // east
        fill(matrix, y+1, x, sq); // south
        fill(matrix, y, x-1, sq); // west
        return;
}

