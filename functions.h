#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROCK   0
#define FOX    1
#define RABBIT 2
#define EMPTY  3

typedef struct{
	int type;
	int gen_proc;
	int gen_food;
}ECO_ELEMENT;

typedef struct{
	int GEN_PROC_RABBITS;
	int GEN_PROC_FOXES;
	int GEN_FOOD_FOXES;
	int N_GEN;
	int R;
	int C;
	int N;
	int size;
}ECO_SETTINGS;

typedef struct {
	int x;
	int y;
}POSITION;


ECO_SETTINGS read_settings(FILE *file);

ECO_ELEMENT* read_gen0(FILE *file, int R, int C, int N);

void clear_fauna(ECO_ELEMENT *new_eco, int size);

void print_gen(ECO_ELEMENT *eco_system, int R, int C, int gen);

void save_result(ECO_SETTINGS settings, ECO_ELEMENT* eco);

POSITION new_position(int gen, ECO_ELEMENT *ecosystem, int i, int j, int R, int C, int type);

void rabbit_pusher(int gen, ECO_ELEMENT* current_eco, ECO_ELEMENT* new_eco, int R, int C, int GEN_PROC_RABBITS);

void fox_pusher(int gen, ECO_ELEMENT* current_eco, ECO_ELEMENT* new_eco, int R, int C, int GEN_PROC_FOXES, int GEN_FOOD_FOXES);

#endif
