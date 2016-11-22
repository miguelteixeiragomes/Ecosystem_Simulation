#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ROCK   '*'
#define FOX    'F'
#define RABBIT 'R'
#define EMPTY  ' '


typedef struct {
	char type;
	int gen_proc;
	int gen_food;
}Eco_element;


int main(int argc, char *argv[]){
	int R = 10, C = 10;

	Eco_element *eco_system = malloc(R*C*sizeof(Eco_element));




	free(eco_system);
	return 0;
}
