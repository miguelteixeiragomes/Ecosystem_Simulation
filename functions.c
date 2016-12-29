#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include "functions.h"

const char types_in_char[4] = {'*', 'F', 'R', ' '};

ECO_SETTINGS read_settings(FILE *file){
	ECO_SETTINGS settings;

	fscanf(file, "%d %d %d %d %d %d %d",  &settings.GEN_PROC_RABBITS,
										  &settings.GEN_PROC_FOXES,
										  &settings.GEN_FOOD_FOXES,
										  &settings.N_GEN,
										  &settings.R,
										  &settings.C,
										  &settings.N);

	return settings;
}

ECO_ELEMENT* read_gen0(FILE *file, int R, int C, int N){
  ECO_ELEMENT* eco_system = malloc(R*C*sizeof(ECO_ELEMENT));
  int idx;
  ECO_ELEMENT new_element;

  for(int I = 0; I < R; I++){
    for(int J = 0; J < C; J++){
      idx = I*C + J;
      new_element.type = EMPTY;
      eco_system[idx] = new_element;
    }
  }

  char string[10];
  int X, Y;
  for(int I = 0; I < N; I++){
    fscanf(file, "%s %d %d", string, &X, &Y);
    idx = X*C + Y;
    if(strcmp(string,"ROCK") == 0){
      new_element.type = ROCK;
    }
    else if(strcmp(string,"FOX") == 0){
      new_element.type = FOX;
    }
    else if(strcmp(string,"RABBIT") == 0){
      new_element.type = RABBIT;
    }
    else{
      new_element.type = EMPTY;
    }
    eco_system[idx] = new_element;
  }

  return eco_system;
}

void print_gen(ECO_ELEMENT *eco_system, int R, int C, int gen){
  char bar[R+1];
  strcpy(bar, "-");
  for (int I = 0; I < 2*R; I++){
    strcat(bar, "-");
  }

  printf("Generation %d\n", gen);
  printf("%s\n", bar);
  int idx;
  for(int I = 0; I < R; I++){
    printf("|");
    for(int J = 0; J < C-1; J++){
      idx = I*C + J;
      printf("%c ", types_in_char[eco_system[idx].type]);
    }
    printf("%c|\n", types_in_char[eco_system[idx+1].type]);
  }
  printf("%s\n", bar);
}

POSITION new_position(int gen, ECO_ELEMENT *ecosystem, int i, int j, int R, int C) {
	int direction[4] = { 0, 0, 0, 0 }; // north, east, south, west
	ECO_ELEMENT elem;
	int idx;
	int size = R*C;

	idx = (i - 1)*C + j;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == EMPTY)
			direction[0]++;
	}
	idx = i*C + j + 1;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == EMPTY)
			direction[1]++;
	}
	idx = (i + 1)*C + j;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == EMPTY)
			direction[2]++;
	}
	idx = i*C + j - 1;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == EMPTY)
			direction[3]++;
	}
	for (int i = 0; i < 4; i++)printf("%d\n", direction[i]);

	int pick = (gen + i + j) % (direction[0] + direction[1] + direction[2] + direction[3]);
	printf("pick = %d\n", pick);
	int dir = 0;
	while (dir < 5) {
		if (direction[dir] == 1) {
			if (pick == 0) {
				break;
			}
			else {
				pick--;
				dir++;
			}
		}
		else {
			dir++;
		}
	}
	POSITION pos;

	switch (dir) {
	case 0:
		pos.x = i - 1;
		pos.y = j;
		return pos;
	case 1:
		pos.x = i;
		pos.y = j + 1;
		return pos;
	case 2:
		pos.x = i + 1;
		pos.y = j;
		return pos;
	case 3:
		pos.x = i;
		pos.y = j - 1;
		return pos;
	case 4:
		pos.x = i;
		pos.y = j;
		return pos;
	}
}

void pusher(int gen, ECO_ELEMENT* ecosystem, int R, int C) {
	int i, j;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			ECO_ELEMENT elem = ecosystem[i*C + j];
			if (elem.type == RABBIT) {
				POSITION pos = new_position(gen, ecosystem, i, j, R, C);

			}
		}
	}
}
