#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stlib.h>

struct Eco_element{
	char type;
	int gen_proc;
	int gen_food;
};

struct ECO_SETTINGS{
	int GEN_PROC_RABBITS;
	int GEN_PROC_FOXES;
  int GEN_FOOD_FOXES;
  int N_GEN;
  int R;
  int C;
  int N;
};

struct ECO_SETTINGS read_settings(FILE *file);
struct Eco_element read_gen0(FILE *file, int R, int C, int N);
void print_gen(struct Eco_element *eco_system, int R, int C, int gen);

#endif
