#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>


int main(int argc, char *argv[]){
	if (argc < 2) {
		printf("No input file supplied\n");
		return 1;
	}

	// Handle reading the input
	FILE *file;
	file = fopen(argv[1], "r");

	ECO_SETTINGS settings = read_settings(file);
	ECO_ELEMENT *array_1 = read_gen0(file, settings.R, settings.C, settings.N);
	fclose(file);

	ECO_ELEMENT *array_2 = malloc(settings.size*sizeof(ECO_ELEMENT));
	memcpy(array_2, array_1, settings.size*sizeof(ECO_ELEMENT));

	// Lets get jiggy with it
	int gen;
	for (gen = 0; gen < settings.N_GEN; gen++) {
		print_gen(array_1, settings.R, settings.C, gen, 1);

		clear_fauna(array_2, settings.size);
		rabbit_pusher(gen, array_1, array_2, settings.R, settings.C, settings.GEN_PROC_RABBITS);

		transmit_type(array_1, array_2, settings.size, FOX);
		printf("array_2 after moving rabbits\n");
		print_gen(array_2, settings.R, settings.C, gen, 1);

		clear_fauna(array_1, settings.size);
		transmit_type(array_2, array_1, settings.size, RABBIT);
		fox_pusher(gen, array_2, array_1, settings.R, settings.C, settings.GEN_PROC_FOXES, settings.GEN_FOOD_FOXES);
	}
	print_gen(array_1, settings.R, settings.C, gen, 1);

	save_result(settings, array_1);

	// Freeeeeeeeeeedom (Mel Gibson)
	free(array_1);
	free(array_2);
	return 0;
}
