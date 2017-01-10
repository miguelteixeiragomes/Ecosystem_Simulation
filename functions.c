#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include "functions.h"

const char types_in_char[4] = {'*', 'F', 'R', ' '};
const char types_in_string[4][8] = {"ROCK", "FOX", "RABBIT", "EMPTY"};
omp_lock_t *lock_matrix;

void instanciate_locks(int size) {
	lock_matrix = (omp_lock_t*)malloc(size * sizeof(omp_lock_t));
	for (int i = 0; i < size; i++) {
		omp_init_lock(&lock_matrix[i]);
	}
}

void destroy_locks(int size) {
	for (int i = 0; i < size; i++) {
		omp_destroy_lock(&lock_matrix[i]);
	}
	free(lock_matrix);
}

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
	  new_element.temp_type = EMPTY;
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

	new_element.gen_food = 0;
	new_element.gen_proc = 0;
    if(strcmp(string,"ROCK") == 0){
      new_element.type = ROCK;
	  new_element.temp_type = ROCK;
    }
    else if(strcmp(string,"FOX") == 0){
      new_element.type = FOX;
	  new_element.temp_type = FOX;
    }
    else if(strcmp(string,"RABBIT") == 0){
      new_element.type = RABBIT;
	  new_element.temp_type = RABBIT;
    }
    else{
      new_element.type = EMPTY;
	  new_element.temp_type = EMPTY;
    }
	// All the same at the begining
    eco_system[idx] = new_element;
  }

  return eco_system;
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
			if (eco_system[idx].type == EMPTY) {
				printf("    ");
			}
			else if (eco_system[idx].type == ROCK) {
				printf("*** ");
			}
			else {
				printf("%c%d%d ", types_in_char[eco_system[idx].type], eco_system[idx].gen_proc, eco_system[idx].gen_food);
			}
		else
			printf("%c", types_in_char[eco_system[idx].type]);
    }
	if (flag == 1) {
		if (eco_system[idx + 1].type == EMPTY) {
			printf("   |\n");
		}
		else if (eco_system[idx + 1].type == ROCK) {
			printf("***|\n");
		}
		else {
			printf("%c%d%d|\n", types_in_char[eco_system[idx + 1].type], eco_system[idx + 1].gen_proc, eco_system[idx + 1].gen_food);
		}
	}
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

	
	if (i - 1 > -1 && i - 1 < R && j > -1 && j < C) {
		idx = (i - 1)*C + j;
		elem = ecosystem[idx];
		if (elem.type == type)
			direction[0]++;
	}
	if (i > -1 && i < R && j + 1 > -1 && j + 1 < C) {
		idx = i*C + j + 1;
		elem = ecosystem[idx];
		if (elem.type == type)
			direction[1]++;
	}
	if (i + 1 > -1 && i + 1 < R && j > -1 && j < C) {
		idx = (i + 1)*C + j;
		elem = ecosystem[idx];
		if (elem.type == type)
			direction[2]++;
	}
	if (i > -1 && i < R && j - 1 > -1 && j - 1 < C) {
		idx = i*C + j - 1;
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
		default:
			pos.x = 0;
			pos.y = 0;
			return pos;
	}
}

void clear_fauna(ECO_ELEMENT *new_eco, int size) {
	#pragma omp for schedule(static)
	for (int i = 0; i < size; i++) {
		//printf("Thread %d - clear fauna idx %d\n", omp_get_thread_num(), i);
		if (new_eco[i].type != ROCK) {
			new_eco[i].type = EMPTY;
			new_eco[i].temp_type = EMPTY;
			new_eco[i].gen_proc = 0;
			new_eco[i].gen_food = 0;
		}
	}
}

void transmit_type(ECO_ELEMENT* current_eco, ECO_ELEMENT* new_eco, int size, int type) {
	#pragma omp for schedule(static)
	for (int i = 0; i < size; i++) {
		//printf("Thread %d - clear fauna idx %d\n", omp_get_thread_num(), i);
		if (current_eco[i].type == type) {
			new_eco[i] = current_eco[i];
		}
	}
}

void rabbit_pusher(int gen, ECO_ELEMENT* current_eco, ECO_ELEMENT* new_eco, int R, int C, int GEN_PROC_RABBITS) {
	int i, j;
	int current_idx, new_idx;

	//#pragma omp for private(i,j)
	#pragma omp barrier
	#pragma omp for private(j) schedule(guided)
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			current_idx = i*C + j;
			if (current_eco[current_idx].type == RABBIT) {
				//printf("Thread %d - got rabbit with idx %d\n", omp_get_thread_num(), current_idx);

				// Calculate new possible position
				POSITION pos = new_position(gen, current_eco, i, j, R, C, EMPTY);
				new_idx = pos.x*C + pos.y;

				if (new_idx != current_idx) {

					if (current_eco[current_idx].gen_proc >= GEN_PROC_RABBITS) {
						// Handles reproduction of the Rabbits
						omp_set_lock(&lock_matrix[current_idx]);

						new_eco[current_idx].type = RABBIT;
						new_eco[current_idx].gen_proc = -1;

						omp_unset_lock(&lock_matrix[current_idx]);
						current_eco[current_idx].gen_proc = -1;
					}

					omp_set_lock(&lock_matrix[new_idx]);
					
					if (new_eco[new_idx].type == EMPTY || (new_eco[new_idx].type == RABBIT && current_eco[current_idx].gen_proc > new_eco[new_idx].gen_proc)) {
						// Solve conflicting Rabbits
						new_eco[new_idx] = current_eco[current_idx];
					}

					omp_unset_lock(&lock_matrix[new_idx]);
				}
				else {
					// Rabbit stays in the same place
					omp_set_lock(&lock_matrix[new_idx]);

					new_eco[new_idx] = current_eco[current_idx];

					omp_unset_lock(&lock_matrix[new_idx]);
				}
			}
		}
	}
	#pragma omp barrier

	#pragma omp for schedule(static)
	for (i = 0; i < R*C; i++) {
		if (new_eco[i].type == RABBIT) {
			new_eco[i].gen_proc++;
			new_eco[i].temp_type = RABBIT;
		}
	}
}

void fox_pusher(int gen, ECO_ELEMENT* current_eco, ECO_ELEMENT* new_eco, int R, int C, int GEN_PROC_FOXES, int GEN_FOOD_FOXES) {
	int i, j;
	int current_idx, new_idx;

	#pragma omp barrier
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			current_idx = i*C + j;
			if (current_eco[current_idx].type == FOX) {

				// Selects te next position based on both rabbits and empy spaces
				POSITION pos = new_position(gen, current_eco, i, j, R, C, RABBIT);
				if (pos.x == i && pos.y == j) {
					pos = new_position(gen, current_eco, i, j, R, C, EMPTY);
				}
				new_idx = pos.x*C + pos.y;

				if (current_idx != new_idx) {
					if (current_eco[current_idx].gen_proc >= GEN_PROC_FOXES && (current_eco[current_idx].gen_food + 1 < GEN_FOOD_FOXES || new_eco[new_idx].temp_type == RABBIT)) {
						// Handles reproduction of the Foxes if they don't starve or move into a Rabbit 
						new_eco[current_idx].type = FOX;
						new_eco[current_idx].gen_proc = -1;
						new_eco[current_idx].gen_food = -1;
						current_eco[current_idx].gen_proc = -1;
					}

					if (new_eco[new_idx].type == RABBIT) {
						// Eat the Rabbit
						new_eco[new_idx] = current_eco[current_idx];
						new_eco[new_idx].gen_food = -1;
						new_eco[new_idx].temp_type = RABBIT;
					}
					else if (new_eco[new_idx].type == EMPTY && current_eco[current_idx].gen_food + 1 < GEN_FOOD_FOXES) {
						// Fox moves to an empty place if it doesn't starve
						new_eco[new_idx] = current_eco[current_idx];
					}
					else if (new_eco[new_idx].type == FOX && current_eco[current_idx].gen_food + 1 < GEN_FOOD_FOXES
						&& (current_eco[current_idx].gen_proc > new_eco[new_idx].gen_proc 
							|| (current_eco[current_idx].gen_proc == new_eco[new_idx].gen_proc 
								&& current_eco[current_idx].gen_food < new_eco[new_idx].gen_food))) {
						// Solve conflicting Foxes
						new_eco[new_idx] = current_eco[current_idx];
					}
				}
				else if (current_eco[current_idx].gen_food + 1 < GEN_FOOD_FOXES) {
					// Fox stays in the same place if it doesn't starve
					new_eco[current_idx] = current_eco[current_idx];
				}
			}
		}
	}
	#pragma omp barrier

	#pragma omp for schedule(static)
	for (i = 0; i < R*C; i++) {
		if (new_eco[i].type == FOX) {
			new_eco[i].gen_proc++;
			new_eco[i].gen_food++;
			new_eco[i].temp_type = FOX;
		}
	}
}