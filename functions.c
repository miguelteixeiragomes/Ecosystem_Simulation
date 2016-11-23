#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define ROCK   '*'
#define FOX    'F'
#define RABBIT 'R'
#define EMPTY  ' '

struct ECO_SETTINGS read_settings(FILE *file){
  struct ECO_SETTINGS settings;

  fscanf(file, "%d %d %d %d %d %d %d",  &settings.GEN_PROC_RABBITS,
                                        &settings.GEN_PROC_FOXES,
                                        &settings.GEN_FOOD_FOXES,
                                        &settings.N_GEN,
                                        &settings.R,
                                        &settings.C,
                                        &settings.N);

  return settings;
}

struct Eco_element read_gen0(FILE *file, int R, int C, int N){
  struct Eco_element *eco_system = malloc(R*C*sizeof(struct Eco_element));

  for(int I = 0; I < R; I++){
    for(int J = 0; J < C; C++){
      int index = I*C + J;
      struct Eco_element empty_element;
      empty_element.type = EMPTY;
      eco_system[index] = empty_element;
    }
  }

  for(int I = 0; I < N; I++){
    char string[10];
    int X;
    int Y;
    fscanf(file, "%s %d %d", string, &X, &Y);
    printf("%s %d %d\n", string, X, Y);
  }

  return *eco_system;
}
