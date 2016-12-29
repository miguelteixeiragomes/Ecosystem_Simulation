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
	ECO_ELEMENT *eco_system = read_gen0(file, settings.R, settings.C, settings.N);
	fclose(file);
	print_gen(eco_system, settings.R, settings.C, 0);

	ECO_ELEMENT *new_eco = malloc(settings.size*sizeof(ECO_ELEMENT));
	memcpy(new_eco, eco_system, settings.size * sizeof(ECO_ELEMENT));
	clear_fauna(new_eco, settings.size);

	// Lets get jiggy with it
	rabbit_pusher(0, eco_system, new_eco, settings.R, settings.C, settings.GEN_PROC_RABBITS);
	print_gen(new_eco, settings.R, settings.C, 1);

	// Freeeeeeeeeeedom (Mel Gibson)
	free(eco_system);
	free(new_eco);
	return 0;
}
