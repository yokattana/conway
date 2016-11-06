#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define WIDTH      1000
#define HEIGHT     1000
#define ITERATIONS 1000

#define IDX(x,y) (WIDTH * ((y) % HEIGHT) + ((x) % WIDTH))
#define ROW(i)   ((i) / WIDTH % HEIGHT)
#define COL(i)   ((i) % WIDTH)

int main(int argc, const char* argv[])
{
	uint8_t* prev = malloc(WIDTH * HEIGHT); if (!prev) goto err;
	uint8_t* curr = malloc(WIDTH * HEIGHT); if (!curr) goto err;
	
	srand(time(NULL));
	for (int i = 0; i < WIDTH * HEIGHT; i++) curr[i] = rand() & 1;

	for (int i = 0; i < ITERATIONS; i++) {
		/* if (!(i % 10)) printf("Iteration %d\n", i); */

		uint8_t* temp = prev;
		prev = curr; curr = temp;

		for (int j = 0; j < WIDTH * HEIGHT; j++) {
			int x = COL(j), y = ROW(j);
			int n = prev[IDX(x-1,y-1)] + prev[IDX(x,y-1)] +
				prev[IDX(x+1,y-1)] + prev[IDX(x-1,y)] +
				prev[IDX(x+1,y)] + prev[IDX(x-1,y+1)] +
				prev[IDX(x,y+1)] + prev[IDX(x+1,y+1)];
			curr[j] = n == 2 || n == 3;
		}
	}

	int sum = 0;
	for (int i = 0; i < WIDTH * HEIGHT; i++) sum += curr[i];
	printf("Checksum: %d\n", sum);
	
	return 0;

err:	perror("conway");
	exit(EXIT_FAILURE);
}
