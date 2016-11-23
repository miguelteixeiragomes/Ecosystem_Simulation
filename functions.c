#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
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

Eco_element* read_gen0(FILE *file, int R, int C, int N){
  Eco_element* eco_system = malloc(R*C*sizeof(Eco_element));
  int idx;
  Eco_element new_element;

  for(int I = 0; I < R; I++){
    for(int J = 0; J < C; J++){
      idx = I*C + J;
      strcpy(new_element.type, " ");
      eco_system[idx] = new_element;
    }
  }

  char string[10];
  int X, Y;
  for(int I = 0; I < N; I++){
    fscanf(file, "%s %d %d", string, &X, &Y);
    idx = X*C + Y;
    if(strcmp(string,"ROCK") == 0){
      strcpy(new_element.type, "*");
    }
    else if(strcmp(string,"FOX") == 0){
      strcpy(new_element.type, "F");
    }
    else if(strcmp(string,"RABBIT") == 0){
      strcpy(new_element.type, "R");
    }
    else{
      strcpy(new_element.type, " ");
    }
    eco_system[idx] = new_element;
  }

  return eco_system;
}

void print_gen(Eco_element *eco_system, int R, int C, int gen){
  char bar[R+1];
  strcpy(bar, "-");
  for (int I = 0; I < 2*R; I++){
    strcat(bar, "-");
  }

  printf("Generation %d\n", gen);
  printf("%s\n", bar);
  int idx;
  for(int I = 0; I < R; I++){
    printf("|");
    for(int J = 0; J < C-1; J++){
      idx = I*C + J;
      printf("%s ", eco_system[idx].type);
    }
    printf("%s|\n", eco_system[idx+1].type);
  }
  printf("%s", bar);
}
