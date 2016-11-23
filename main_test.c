#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define ROCK   '*'
#define FOX    'F'
#define RABBIT 'R'
#define EMPTY  ' '

int main(int argc, char *argv[]){
  if (argc < 2) {
    printf("No input file supplied\n");
    return 1;
  }

  FILE *file;
  file = fopen(argv[1], "r");

  ECO_SETTINGS settings = read_settings(file);

  printf("GEN_PROC_RABBITS %d\n", settings.GEN_PROC_RABBITS);
  printf("GEN_PROC_FOXES %d\n", settings.GEN_PROC_FOXES);
  printf("GEN_FOOD_FOXES %d\n", settings.GEN_FOOD_FOXES);
  printf("N_GEN %d\n", settings.N_GEN);
  printf("R %d\n", settings.R);
  printf("C %d\n", settings.C);
  printf("N %d\n", settings.N);

  Eco_element *eco_system;
  eco_system =

  fclose(file);

	return 0;
}
