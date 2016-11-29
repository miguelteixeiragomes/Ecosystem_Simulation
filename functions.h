#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	char type[2];
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
}ECO_SETTINGS;

typedef struct {
	int x;
	int y;
}POSITION;


ECO_SETTINGS read_settings(FILE*);
ECO_ELEMENT* read_gen0(FILE*, int, int, int);
void print_gen(ECO_ELEMENT*, int, int, int);
POSITION new_position(int, ECO_ELEMENT*, int, int, int, int)

#endif
