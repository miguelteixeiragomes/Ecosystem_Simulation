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

	FILE *file;
	file = fopen(argv[1], "r");

	ECO_SETTINGS settings = read_settings(file);
	ECO_ELEMENT *eco_system = read_gen0(file, settings.R, settings.C, settings.N);
	print_gen(eco_system, settings.R, settings.C, 0);

	fclose(file);
  
	POSITION pos = new_position(1, eco_system, 0, 2, settings.R, settings.C);
	printf("%d %d\n", pos.x, pos.y);

	return 0;
}
