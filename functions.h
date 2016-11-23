#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stlib.h>

typedef struct {
	char type;
	int gen_proc;
	int gen_food;
}Eco_element;

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

#endif
