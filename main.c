#include <omp.h>
#include <stdio.h>

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

	Eco_element *eco_system = (*Eco_element)malloc(R*C*sizeof(Eco_element));

	return 0;
}
