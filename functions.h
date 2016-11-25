#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char type[2];
	int gen_proc;
	int gen_food;
}Eco_element;

typedef struct{
	int GEN_PROC_RABBITS;
	int GEN_PROC_FOXES;
  int GEN_FOOD_FOXES;
  int N_GEN;
  int R;
  int C;
  int N;
}ECO_SETTINGS;

ECO_SETTINGS read_settings(FILE *file);
Eco_element* read_gen0(FILE *file, int R, int C, int N);
void print_gen(Eco_element *eco_system, int R, int C, int gen);

#endif
