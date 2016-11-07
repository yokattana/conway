#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define WIDTH      1002
#define HEIGHT     1002
#define ITERATIONS 1000

#define IDX(x,y) (WIDTH*(y) + (x))

static void copy_borders(uint8_t* grid)
{
	for (int x = 1; x < WIDTH-2; x++) {
		grid[IDX(x,0)] = grid[IDX(x,HEIGHT-2)];
		grid[IDX(x,HEIGHT-1)] = grid[IDX(x,1)];
	}

	for (int y = 1; y < HEIGHT-2; y++) {
		grid[IDX(0,y)] = grid[IDX(WIDTH-2,y)];
		grid[IDX(WIDTH-1,y)] = grid[IDX(1,y)];
	}

	grid[IDX(0,0)] = grid[IDX(WIDTH-2,HEIGHT-2)];
	grid[IDX(WIDTH-1,0)] = grid[IDX(2,HEIGHT-2)];
	grid[IDX(WIDTH-1,HEIGHT-1)] = grid[IDX(1,1)];
	grid[IDX(0,HEIGHT-1)] = grid[IDX(WIDTH-2,1)];
}

int main(int argc, const char* argv[])
{
	uint8_t* prev = malloc(WIDTH * HEIGHT); if (!prev) goto err;
	uint8_t* curr = malloc(WIDTH * HEIGHT); if (!curr) goto err;
	
	srand(time(NULL));
	for (int i = 0; i < WIDTH * (HEIGHT-1); i++) curr[i] = rand() & 1;
	copy_borders(curr);

	for (int i = 0; i < ITERATIONS; i++) {
		/* if (!(i % 10)) printf("Iteration %d\n", i); */

		uint8_t* temp = prev;
		prev = curr; curr = temp;

		for (int j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
			curr[j] = prev[j-WIDTH-1];
		for (int j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
			curr[j] += prev[j-WIDTH];
		for (int j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
			curr[j] += prev[j-WIDTH+1];
		for (int j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
			curr[j] += prev[j-1];
		for (int j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
			curr[j] += prev[j+1];
		for (int j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
			curr[j] = prev[j+WIDTH-1];
		for (int j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
			curr[j] += prev[j+WIDTH];
		for (int j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
			curr[j] += prev[j+WIDTH+1];
		for (int j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
			curr[j] = curr[j] == 3 || (prev[j] && curr[j] == 2);
		
		copy_borders(curr);
	}

	int sum = 0;
	for (int i = 0; i < WIDTH * HEIGHT; i++) sum += curr[i];
	printf("Checksum: %d\n", sum);
	
	return 0;

err:	perror("conway");
	exit(EXIT_FAILURE);
}
