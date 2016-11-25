#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define ROCK   '*'
#define FOX    'F'
#define RABBIT 'R'
#define EMPTY  ' '

int* new_position(int gen, Eco_element* ecosystem, int i, int j, int R, int C) {
	int direction[4] = { 0, 0, 0, 0 }; // north, east, south, west
	Eco_element elem;
	int idx;
	int size = R*C;

	idx = (i - 1)*C + j;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == ' ')
			direction[0]++;
	}
	idx = i*C + j + 1;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == ' ')
			direction[1]++;
	}
	idx = (i + 1)*C + j;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == ' ')
			direction[2]++;
	}
	idx = i*C + j - 1;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == ' ')
			direction[3]++;
	}

	int pick = (gen + i + j) % (direction[0] + direction[1] + direction[2] + direction[3]);

	int dir = 0;
	while (pick > 0) {
		if (direction[dir] == 1) {
			pick--;
			dir++;
		}
		else {
			dir++
		}
	}
	switch (dir) {
	case 0:
		int ret[2] = { i - 1, j     };
		return ret;
	case 1:
		int ret[2] = { i    , j + 1 };
		return ret;
	case 2:
		int ret[2] = { i + 1, j     };
		return ret;
	case 3:
		int ret[2] = { i    , j - 1 };
		return ret;
	}
}


void pusher(int gen, Eco_element* ecosystem, int R, int C) {
	int i, j;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			Eco_element elem = ecosystem[i*C + j];
			if (elem.type == RABBIT) {
				int *pos = new_position(gen, ecosystem, i, j, R, C);

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
