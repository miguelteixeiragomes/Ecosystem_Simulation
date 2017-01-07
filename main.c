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
	ECO_ELEMENT *current_eco = read_gen0(file, settings.R, settings.C, settings.N);
	fclose(file);

	ECO_ELEMENT *new_eco = malloc(settings.size*sizeof(ECO_ELEMENT));
	memcpy(new_eco, current_eco, settings.size * sizeof(ECO_ELEMENT));

	ECO_ELEMENT *aux_eco = current_eco;

	// Lets get jiggy with it
	int gen;
	for (gen = 0; gen < settings.N_GEN; gen++) {
		print_gen(current_eco, settings.R, settings.C, gen);
		clear_fauna(new_eco, settings.size);
		rabbit_pusher(gen, current_eco, new_eco, settings.R, settings.C, settings.GEN_PROC_RABBITS);
		//print_gen(new_eco, settings.R, settings.C, gen);
		fox_pusher(gen, current_eco, new_eco, settings.R, settings.C, settings.GEN_PROC_FOXES, settings.GEN_FOOD_FOXES);
		//print_gen(new_eco, settings.R, settings.C, gen);
		aux_eco = current_eco;
		current_eco = new_eco;
		new_eco = aux_eco;
	}
	print_gen(current_eco, settings.R, settings.C, gen);

	save_result(settings, current_eco);

	// Freeeeeeeeeeedom (Mel Gibson)
	free(current_eco);
	free(new_eco);
	return 0;
}
