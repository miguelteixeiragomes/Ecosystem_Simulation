ecosystem: main.c
	gcc functions.c main.c -o ecosystem -fopenmp -O3
# -mtune=native -march=native
