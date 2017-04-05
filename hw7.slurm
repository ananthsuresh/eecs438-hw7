#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --output=threadedmerge.txt 

cp serialmerge threadedmerge $PFSDIR/.
cd $PFSDIR

echo Serial on Array Size of 20 Million
./serialmerge 20000000
echo Serial on Array Size of 40 Million
./serialmerge 40000000
echo Serial on Array Size of 60 Million
./serialmerge 60000000
echo Serial on Array Size of 80 Million
./serialmerge 80000000
echo Serial on Array Size of 100 Million
./serialmerge 100000000

echo 2 Threads on Array Size of 20 Million 
./threadedmerge 20000000 2
echo 2 Threads on Array Size of 40 Million
./threadedmerge 40000000 2
echo 2 Threads on Array Size of 60 Million
./threadedmerge 60000000 2
echo 2 Threads on Array Size of 80 Million
./threadedmerge 80000000 2
echo 2 Threads on Array Size of 100 Million
./threadedmerge 100000000 2

echo 4 Threads on Array Size of 20 Million 
./threadedmerge 20000000 4
echo 4 Threads on Array Size of 40 Million
./threadedmerge 40000000 4
echo 4 Threads on Array Size of 60 Million
./threadedmerge 60000000 4
echo 4 Threads on Array Size of 80 Million
./threadedmerge 80000000 4
echo 4 Threads on Array Size of 100 Million
./threadedmerge 100000000 4

echo 8 Threads on Array Size of 20 Million 
./threadedmerge 20000000 8
echo 8 Threads on Array Size of 40 Million
./threadedmerge 40000000 8
echo 8 Threads on Array Size of 60 Million
./threadedmerge 60000000 8
echo 8 Threads on Array Size of 80 Million
./threadedmerge 80000000 8
echo 8 Threads on Array Size of 100 Million
./threadedmerge 100000000 8


