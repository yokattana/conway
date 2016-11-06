'use strict';

var WIDTH = 1002;
var HEIGHT = 1002;
var ITERATIONS = 1000;

function idx(x, y) { return WIDTH * y + x; }

function copyBorders(grid)
{
	for (var x = 1; x < WIDTH-2; x++) {
		grid[idx(x,0)] = grid[idx(x,HEIGHT-2)];
		grid[idx(x,HEIGHT-1)] = grid[idx(x,1)];
	}

	for (var y = 1; y < HEIGHT-2; y++) {
		grid[idx(0,y)] = grid[idx(WIDTH-2,y)];
		grid[idx(WIDTH-1,y)] = grid[idx(1,y)];
	}

	grid[idx(0,0)] = grid[idx(WIDTH-2,HEIGHT-2)];
	grid[idx(WIDTH-1,0)] = grid[idx(2,HEIGHT-2)];
	grid[idx(WIDTH-1,HEIGHT-1)] = grid[idx(1,1)];
	grid[idx(0,HEIGHT-1)] = grid[idx(WIDTH-2,1)];
}

var prev = [];
for (var j = 0; j < WIDTH*HEIGHT; j++) prev[j] = 0;

var curr = [];
for (var j = 0; j < WIDTH*HEIGHT; j++) curr[j] = Math.floor(Math.random()*2);

for (var i = 0; i < ITERATIONS; i++) {
	/* if (!(i % 10)) console.log('Iteration ' + i); */

	var temp = prev;
	prev = curr; curr = temp;

	for (var j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
		curr[j] = prev[j-WIDTH-1];
	for (var j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
		curr[j] += prev[j-WIDTH];
	for (var j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
		curr[j] += prev[j-WIDTH+1];
	for (var j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
		curr[j] += prev[j-1];
	for (var j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
		curr[j] += prev[j+1];
	for (var j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
		curr[j] = prev[j+WIDTH-1];
	for (var j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
		curr[j] += prev[j+WIDTH];
	for (var j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
		curr[j] += prev[j+WIDTH+1];
	for (var j = WIDTH; j < WIDTH*(HEIGHT-1); j++)
		curr[j] = curr[j] == 3 || (prev[j] && curr[j] == 2);
	
	copyBorders(curr);
}

var sum = 0;
for (var i = 0; i < WIDTH*HEIGHT; i++) sum += curr[i];
console.log('Checksum: ' + sum);
