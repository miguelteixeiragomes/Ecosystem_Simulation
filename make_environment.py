import sys
import random


if  len(sys.argv) != 10:
    raise ValueError("Arguments for all arguments needed -> (GEN_PROC_RABBITS, GEN_PROC_FOXES, GEN_FOOD_FOXES, N_GEN, R, C, ROCK, RABBIT, FOX)")

GEN_PROC_RABBITS, GEN_PROC_FOXES, GEN_FOOD_FOXES, N_GEN, R, C, ROCK, RABBIT, FOX = [int(i) for i in sys.argv[1:]]

if (ROCK + FOX + RABBIT) >= R*C:
    raise ValueError("Too many objects for such a small environment.")


positions = []
for i in range(R):
    for j in range(C):
        positions.append( (i, j) )

fich = open("input%sx%s.txt" % (R, C), 'w')
fich.write("%d %d %d %d %d %d %d\n" % (GEN_PROC_RABBITS, GEN_PROC_FOXES, GEN_FOOD_FOXES, N_GEN, R, C, ROCK + RABBIT + FOX))


for i in range(ROCK):
    idx = random.randrange(len(positions))
    position = positions[idx]
    del(positions[idx])
    fich.write("ROCK %d %d\n" % position)

for i in range(RABBIT):
    idx = random.randrange(len(positions))
    position = positions[idx]
    del(positions[idx])
    fich.write("RABBIT %d %d\n" % position)

for i in range(FOX):
    idx = random.randrange(len(positions))
    position = positions[idx]
    del(positions[idx])
    fich.write("FOX %d %d\n" % position)
