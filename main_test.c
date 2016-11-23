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

  struct ECO_SETTINGS settings = read_settings(file);
  struct Eco_element eco_system = read_gen0(file, settings.R, settings.C, settings.N);

  fclose(file);

	return 0;
}
