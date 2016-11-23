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

  char string[10];
  int X, Y, index;
  struct Eco_element new_element;
  for(int I = 0; I < N; I++){
    fscanf(file, "%s %i %i", string, &X, &Y);
    index = X * C + Y;
    printf("%s %d %d index = %d\n", string, X, Y, X*C+Y);
    // if(string == "ROCK"){
    //   new_element.type = ROCK;
    // }
    // else if(string == "FOX"){
    //   new_element.type = FOX;
    // }
    // else if(string == "RABBIT"){
    //   new_element.type == RABBIT;
    // }
    // else{
    //   new_element.type = EMPTY;
    // }
    // eco_system[index] = new_element;
  }

  return *eco_system;
}

// void print_gen(struct Eco_element eco_system, int R, int C, int N){
//
// }
