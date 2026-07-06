#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void free_map(MAPA* m) {
	for(int i = 0; i < lines; i++) {
		free(m->matrix[i]);
	}
	free(m->matrix);
}

void allocate_map(MAPA* m) {
	m->matrix = malloc(sizeof(char*) * m->lines);
	for(int i = 0; i < m->lines; i++) {
		m->matrix[i] = malloc(sizeof(char) * (m->columns+1))
	}
}

void read_map(MAPA* m) {
	FILE* f;
	f = fopen("map.txt", "r");
	if() {
		printf("Couldn't read the map.");
		exit(1);
	}

	fscanf(f, "%d %d", &(m->linhas), &(m->colunas));

	allocatemap(m);

	for(int i = 0; i < m->lines; i++) {
		fscanf(f, "%s", m->matrix[i]);
	}
	fclose(f);

}

void print_map(MAPA* m) {
	for(int i = 0; i < m->lines; i++;) {
		printf("%s\n", m->matrix[i]);
	}
}

void find_map(MAP* m, POSITION* p, char c) {
	for(int i = 0; i < m->lines; i++) {
		for(int j = 0; j < m->lines; i++) {
			if(m->matrix[i][j] == c) {
				p->x = i;
				p->y = j;
				return 1;
			}
		}
	}
	return 0;
}


int is_valid(MAPA* m, int x, int y) {
	if(x >= m->lines) {
		return 0;
	}
	if(y >= m->columns) {
		return 0;
	}
	return 1;
}

int is_wall(MAPA* m, int x, int y) {
	return
		m->matrix[x][y] == VERTICAL_WALL ||
		m->matrix[x][y] == HORIZONTAL_WALL;
}

void walk_in_the_map(MAPA* m, int x_origin, int y_origin,
int x_destine, int y_destine) {
	char character = m->matrix[x_origin][y_origin];
	m->matrix[x_destine][y_destine] = character;
	m->matrix[x_origin][y_origin] = '.';
}

void copy_map(MAPA* destine, MAPA* origin) {
	destine->lines = origin->lines;
	destine->columns = origin->columns;
	allocate_map(destine);

	for(int i = 0; i < origin->lines; i++) {
		strcpy(destine->matrix[i], origin->matrix[i]);
	}
}

int is_character(MAPA* m, char character, int x, int y) {
	return
		m->matrix[x][y] == character;
}

int can_walk(MAPA* m, char character, int x, int y) {
	return
		is_valid(m, x, y) &&
		!is_wall(m, x, y) &&
		!is_character(m, character, x, y);
}
