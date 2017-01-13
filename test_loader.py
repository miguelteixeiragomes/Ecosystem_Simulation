import os
import make_environment

if __name__ == '__main__':

    GEN_PROC_RABBITS = 3
    GEN_PROC_FOXES = 20
    GEN_FOOD_FOXES = 10
    N_GEN = 10000
    ROCK = 1
    RABBIT = 1
    FOX = 1

    N_THREADS = [1, 2, 4, 8, 16, 32, 64]

    # Generate files and run them
    INPUT_FILES = ["input5x5", "input100x100", "input200x200", "input1000x1000"]

    for file_name in INPUT_FILES:
        output_file = file_name + "_output"
        f = open(output_file, "w+")
        f.close()
        for N in N_THREADS:
            os.system("./ecosystem.exe ./%s %d >> %s" % (file_name, N, output_file))
