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
	int NUM_THREADS;
	if (argc == 3) {
		NUM_THREADS = atoi(argv[2]);
	}
	else {
		NUM_THREADS = omp_get_max_threads();
	}
	if (NUM_THREADS > omp_get_max_threads()) {
		printf("Can't launch %d threads, using system limit: %d\n", NUM_THREADS, omp_get_max_threads());
		NUM_THREADS = omp_get_max_threads();
	}
	omp_set_num_threads(NUM_THREADS);

	//printf("Executing with %d threads\n", NUM_THREADS);

	// Handle reading the input
	FILE *file;
	file = fopen(argv[1], "r");

	ECO_SETTINGS settings = read_settings(file);
	ECO_ELEMENT *array_1 = read_gen0(file, settings.R, settings.C, settings.N);
	fclose(file);

	ECO_ELEMENT *array_2 = malloc(settings.size*sizeof(ECO_ELEMENT));
	memcpy(array_2, array_1, settings.size*sizeof(ECO_ELEMENT));
	
	instanciate_locks(settings.size);

	// Lets get jiggy with it
	int gen;
	double start, stop;
	start = omp_get_wtime();

	#pragma omp parallel private(gen) shared(settings, array_1, array_2)
	{
		for (gen = 0; gen < settings.N_GEN; gen++) {

			//#pragma omp master
			//print_gen(array_1, settings.R, settings.C, gen, 0);

			#pragma omp barrier
			clear_fauna(array_2, settings.size);
			rabbit_pusher(gen, array_1, array_2, settings.R, settings.C, settings.GEN_PROC_RABBITS);
			transmit_type(array_1, array_2, settings.size, FOX);

			clear_fauna(array_1, settings.size);
			transmit_type(array_2, array_1, settings.size, RABBIT);
			fox_pusher(gen, array_2, array_1, settings.R, settings.C, settings.GEN_PROC_FOXES, settings.GEN_FOOD_FOXES);
		}
	}
	stop = omp_get_wtime();

	//print_gen(array_1, settings.R, settings.C, settings.N_GEN, 0);
	printf("%d\t%f\n", NUM_THREADS, stop - start);

	save_result(settings, array_1);

	// Freeeeeeeeeeedom (Mel Gibson)
	destroy_locks(settings.size);
	free(array_1);
	free(array_2);
	return 0;
}
