#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
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
  int idx;
  struct Eco_element new_element;

  for(int I = 0; I < R; I++){
    for(int J = 0; J < C; J++){
      idx = I*C + J;
      new_element.type = EMPTY;
      eco_system[idx] = new_element;
    }
  }

  char string[10];
  int X, Y;
  for(int I = 0; I < N; I++){
    fscanf(file, "%s %d %d", string, &X, &Y);
    idx = X*C + Y;
    if(strcmp(string,"ROCK") == 0){
      new_element.type = ROCK;
    }
    else if(strcmp(string,"FOX") == 0){
      new_element.type = FOX;
    }
    else if(strcmp(string,"RABBIT") == 0){
      new_element.type == RABBIT;
    }
    else{
      new_element.type = EMPTY;
    }
    eco_system[idx] = new_element;
  }
  return *eco_system;
}

// void print_gen(struct Eco_element *eco_system, int R, int C, int gen){
//   int idx;
//   for(int I = 0; I < R; I++){
//     for(int J = 0; I < C; J++){
//       idx = I*C + J;
//       printf("%s", eco_system[idx].type);
//     }
//     printf("\n");
//   }
// }
