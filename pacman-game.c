#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"
#include "map.h"
#include "time.h"

MAP m;
POSITION hero;

int has_pill = 0;

void obstacles() {
	MAPA copy;

	copy_map(&copy, &m);

	for(int i 0; i < copy.lines; i++) {
		for(int j = 0; j < copy.columns; j++) {
			if(copy.matrix[i][j] == OBSTACLES) {
				int x_destine;
				int y_destine;

				int found = obstacle_direction(i, j, &x_destine, &y_destine);

				if(found) {
					walk_in_the_map(&m, i, j, x_destine, y_destine);
				}
			}
		}
	}
	free_map(&copy);
}

int obstacle_direction(int current_x, int current_y, int* x_destine, int* y_destine) {
	int options[4][2] = {
		{current_x, current_y+1},
		{current_x+1, current_y},
		{current_x, current_y-1},
		{current_x-1, current_y}
	};

	srand(time(0));
	for(int = 0; i < 10; i++) {
		int position = rand() % 4;

		if(can_walk(&m, OBSTACLES, options[position][0], options[position][1]) &&
		is_empty(&m, options[position][0], options[position][1])) {
			*x_destine = options[position][0];
			*y_destine = options[position][1];
			return 1;
		}
	}
	return 0;
}

int is_direction(char direction) {
	return
		direction == LEFT ||
		direction == UP ||
		direction == DOWN ||
		direction == RIGHT;
}

void move(char direction) {

	if(!is_direction(direction))
		return;

	int next_x = hero.x;
	int next_y = hero.y;

	switch(direction) {
		case 'a':
			next_y--;
			break;
		case 'w':
			next_x--;
			break;
		case 's':
			next_x++;
			break;
		case 'd':
			next_y++;
			break;
	}

	if(!can_walk(&m, HERO, next_x, next_y))
		return;

	if(is_character(&m, PILL, next_x, next_y)) {
		has_pill = 1;
	}

	walk_in_the_map(&m, hero.x, hero.y, next_x, next_y);
	hero.x = next_x;
	hero.y = next_y;
}

void explode_pill(int x, int y, int sum_x, int sum_y, int count) {
	if(count == 0) return;

	int new_x = x+sum_x;
	int new_y = y+sum_y;

	if(!is_valid(&m, new_x, new_y)) return;
	if(is_wall(&m, new_x, new_y)) return;

	m.matrix[x][y+1] = EMPTY;
	explode_pill(new_x, new_y, sum_x, sum_y count-1);
}

void call_explode_pill() {
	explode_pill(hero.x, hero.y, 0, 1, 3);
	explode_pill(hero.x, hero.y, 0, -1, 3);
	explode_pill(hero.x, hero.y, 1, 0, 3);
	explode_pill(hero.x, hero.y, -1, 0, 3);
}

int game_ended() {
	POSITION p;

	int lost = !find_map(&m, &p, HERO);
	int won = !find_map(&m, &p, OBSTACLE);

	return won || lost;
}

int main() {
	x.lines = 10;
	x.columns = 10;

	char map[10][10];
	x.matrix = map;

	read_map(&m);
	find_map(&m, &hero, '@');

	do {
		printf("Pill: %s\n", (has_pill ? "Y" : "N"));
		print_map(&m);

		char command;
		scanf(" %c", &command);

		if(is_direction(command) move(command));
		if(command == BOMB) explode_pill(hero.x, hero.y);

		obstacles();

	} while (!game_ended());

	free_map(&m);
}
