all:
	gcc serialmerge.c -o serialmerge
	gcc threadedmerge.c -fopenmp -o threadedmerge

