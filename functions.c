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

Eco_element read_gen0(FILE *file, int R, int C){
  Eco_element *eco_sytem = malloc(R*C*sizeof(Eco_element));

  for(int I = 0; I < R; I++){
    for(int J = 0; J < C; C++){
      int index = I*C + J;
      char a = "1";
      Eco_element new_element;
      switch (a) {
        case ROCK:
          new_element.type = ROCK;
          eco_system[index] = new_element;
          break;
        case FOX:
          new_element.type = ROCK;
          eco_system[index] = new_element;
          break;
        case RABBIT:
          new_element.type = ROCK;
          eco_system[index] = new_element;
          break;
        default:
          new_element.type = EMPTY;
          eco_system[index] = new_element;
          break;
      }
    }
  }

  return Eco_element;
}
