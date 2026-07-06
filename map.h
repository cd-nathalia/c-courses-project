struct map {
	char** matrix;
	int lines;
	int columns;
};

typedef struct map MAP;

void allocate_map();
void read_map();
void free_map();
void print_map();
void find_map();

struct position {
	int x;
	int y;
};

typedef struct position POSITION;

#define HERO '@'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
