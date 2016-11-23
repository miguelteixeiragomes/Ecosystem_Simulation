#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define ROCK   '*'
#define FOX    'F'
#define RABBIT 'R'
#define EMPTY  ' '

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
