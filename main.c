#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ROCK   '*'
#define FOX    'F'
#define RABBIT 'R'
#define EMPTY  ' '


typedef struct {
	char type;
	int gen_proc;
	int gen_food;
}Eco_element;


int* new_position(int gen, Eco_element* ecosystem, int i, int j, int R, int C) {
	bool north, east, south, west;
	Eco_element elem = ecosystem[(i - 1)*C + j];
	if (elem.type == ' ')
		north = true;
	elem = ecosystem[i*C + j + 1];
	if (elem.type == ' ')
		east = true;
	elem = ecosystem[(i + 1)*C + j];
	if (elem.type == ' ')
		south = true;
	elem = ecosystem[i*C + j - 1];
	if (elem.type == ' ')
		west = true;

	
}


void pusher(Eco_element* ecosystem, int R, int C) {
	int i, j;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			Eco_element elem = ecosystem[i*C + j];
			if (elem.type == RABBIT) {
				local_solver_rabbit(ecosystem, elem, R, C, i, j);
			}
		}
	}
}


int main(int argc, char *argv[]){
	int R = 10, C = 10;

	Eco_element *eco_system = malloc(R*C*sizeof(Eco_element));




	free(eco_system);
	return 0;
}
