#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include "functions.h"

const char types_in_char[4] = {'*', 'F', 'R', ' '};
const char types_in_string[4][8] = {"ROCK", "FOX", "RABBIT", "EMPTY"};

ECO_SETTINGS read_settings(FILE *file){
	ECO_SETTINGS settings;

	fscanf(file, "%d %d %d %d %d %d %d",  &settings.GEN_PROC_RABBITS,
										  &settings.GEN_PROC_FOXES,
										  &settings.GEN_FOOD_FOXES,
										  &settings.N_GEN,
										  &settings.R,
										  &settings.C,
										  &settings.N);

	settings.size = settings.R * settings.C;
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
	  new_element.gen_food = 0;
	  new_element.gen_proc = 0;
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
	// All the same at the begining
	new_element.gen_food = 0;
	new_element.gen_proc = 0;
    eco_system[idx] = new_element;
  }

  return eco_system;
}

void clear_fauna(ECO_ELEMENT *new_eco, int size) {
	for (int i = 0; i < size; i++) {
		if (new_eco[i].type != ROCK) {
			new_eco[i].type = EMPTY;
			new_eco[i].gen_proc = 0;
			new_eco[i].gen_food = 0;
		}
	}
}

void print_gen(ECO_ELEMENT *eco_system, int R, int C, int gen, int flag){
  char *bar = malloc((R+1)*sizeof(char));
  strcpy(bar, "-");
  for (int I = 0; I <= R; I++){
    strcat(bar, "-");
  }

  printf("Generation %d\n", gen);
  printf("%s\n", bar);
  int idx;
  for(int I = 0; I < R; I++){
    printf("|");
    for(int J = 0; J < C-1; J++){
		idx = I*C + J;
		if (flag == 1)
			printf("%c%d%d ", types_in_char[eco_system[idx].type], eco_system[idx].gen_proc, eco_system[idx].gen_food);
		else
			printf("%c", types_in_char[eco_system[idx].type]);
    }
	if (flag == 1)
		printf("%c%d%d|\n", types_in_char[eco_system[idx+1].type], eco_system[idx+1].gen_proc, eco_system[idx+1].gen_food);
	else
		printf("%c|\n", types_in_char[eco_system[idx + 1].type]);
  }
  printf("%s\n\n", bar);
}

void save_result(ECO_SETTINGS settings, ECO_ELEMENT* eco) {
	FILE *f = fopen("output.txt", "w+");

	int i, j, current_idx;
	int N = 0;
	for (i = 0; i < settings.size; i++) {
		if (eco[i].type != EMPTY) {
			N++;
		}
	}

	fprintf(f, "%d %d %d %d %d %d %d\n", settings.GEN_PROC_RABBITS, 
									settings.GEN_PROC_FOXES, 
									settings.GEN_FOOD_FOXES,
									0,
									settings.R,
									settings.C,
									N);

	for (i = 0; i < settings.R; i++) {
		for (j = 0; j < settings.C; j++) {
			current_idx = i*settings.C + j;
			if (eco[current_idx].type != EMPTY) {
				fprintf(f, "%s %d %d\n", types_in_string[eco[current_idx].type], i, j);
			}
		}
	}

	fclose(f);
}

POSITION new_position(int gen, ECO_ELEMENT *ecosystem, int i, int j, int R, int C, int type) {
	int direction[4] = { 0, 0, 0, 0 }; // north, east, south, west
	ECO_ELEMENT elem;
	int idx;
	int size = R*C;

	idx = (i - 1)*C + j;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == type)
			direction[0]++;
	}
	idx = i*C + j + 1;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == type)
			direction[1]++;
	}
	idx = (i + 1)*C + j;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == type)
			direction[2]++;
	}
	idx = i*C + j - 1;
	if ((idx > -1) && (idx < size)) {
		elem = ecosystem[idx];
		if (elem.type == type)
			direction[3]++;
	}
	POSITION pos;
	int pick = direction[0] + direction[1] + direction[2] + direction[3];
	if (pick == 0) {
		pos.x = i;
		pos.y = j;
		return pos;
	}
	pick = (gen + i + j) % pick;
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

void rabbit_pusher(int gen, ECO_ELEMENT* current_eco, ECO_ELEMENT* new_eco, int R, int C, int GEN_PROC_RABBITS) {
	int i, j;
	int current_idx, new_idx;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			current_idx = i*C + j;
			if (current_eco[current_idx].type == RABBIT) {
				// Calculate new possible position
				POSITION pos = new_position(gen, current_eco, i, j, R, C, EMPTY);
				new_idx = pos.x*C + pos.y;
				if (new_eco[new_idx].type == EMPTY || (new_eco[new_idx].type == RABBIT && current_eco[current_idx].gen_proc > new_eco[new_idx].gen_proc)) {
					// Move to new position if rules are obeyed
					new_eco[new_idx] = current_eco[current_idx];
					if (current_eco[current_idx].gen_proc >= GEN_PROC_RABBITS) {
						// Drop a kiddo on the old spot
						new_eco[current_idx].type = RABBIT;
						new_eco[current_idx].gen_proc = -1;
						// Gotta wait for more kiddos
						new_eco[new_idx].gen_proc = -1;
					}
				}
				else {
					// GET REKT SON
					printf("chuta um erro\n");
					// Force segmentation fault
					printf("%s", 1);
				}
			}
		}
	}
	for (i = 0; i < R*C; i++) {
		if (new_eco[i].type == RABBIT) {
			new_eco[i].gen_proc++;
		}
	}
}

void transmit_type(ECO_ELEMENT* current_eco, ECO_ELEMENT* new_eco, int size, int type) {
	for (int i = 0; i < size; i++) {
		if (current_eco[i].type == type) {
			new_eco[i] = current_eco[i];
		}
	}
}

void fox_pusher(int gen, ECO_ELEMENT* current_eco, ECO_ELEMENT* new_eco, int R, int C, int GEN_PROC_FOXES, int GEN_FOOD_FOXES) {
	int i, j;
	int current_idx, new_idx;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			current_idx = i*C + j;
			if (current_eco[current_idx].type == FOX) {
				// handles the starvation of foxes
				if (current_eco[current_idx].gen_food >= GEN_FOOD_FOXES) {
					current_eco[current_idx].type = EMPTY;
					current_eco[current_idx].gen_food = 0;
					current_eco[current_idx].gen_proc = 0;
				}

				else {
					// selects te next position based on both rabbits and empy spaces
					POSITION pos = new_position(gen, current_eco, i, j, R, C, RABBIT);
					if (pos.x == i && pos.y == j) {
						pos = new_position(gen, current_eco, i, j, R, C, EMPTY);
					}
					new_idx = pos.x*C + pos.y;

					// if the fox moves
					if (current_idx != new_idx) {
						if (current_eco[new_idx].type == RABBIT) {
							new_eco[new_idx] = current_eco[current_idx];
							new_eco[new_idx].gen_food = -1;
						}
						else if (current_eco[new_idx].type == EMPTY) {
							new_eco[new_idx] = current_eco[current_idx];
						}
						else if (new_eco[new_idx].type == FOX) {
							if (current_eco[current_idx].gen_proc > new_eco[new_idx].gen_proc) {
								new_eco[new_idx] = current_eco[current_idx];
							}
							else if (current_eco[current_idx].gen_proc == new_eco[new_idx].gen_proc) {
								if (current_eco[current_idx].gen_food < new_eco[new_idx].gen_food) {
									new_eco[new_idx] = current_eco[current_idx];
								}
							}
						}
						// handles reproduction of the foxes
						if (current_eco[current_idx].gen_proc >= GEN_PROC_FOXES) {
							new_eco[current_idx].type = FOX;
							new_eco[current_idx].gen_proc = -1;
							new_eco[current_idx].gen_food = -1;
							new_eco[new_idx].gen_proc = -1;
						}
						// If it doesn't reproduce new spot must be EMPTY 
						/*else {
							new_eco[current_idx].type = EMPTY;
							new_eco[current_idx].gen_proc = 0;
							new_eco[current_idx].gen_food = 0;
						}*/
					}
					
					// the fox stays put
					else {
						new_eco[current_idx] = current_eco[current_idx];
					}
				}
			}
		}
	}
	for (i = 0; i < R*C; i++) {
		if (new_eco[i].type == FOX) {
			new_eco[i].gen_proc++;
			new_eco[i].gen_food++;
		}
	}
}