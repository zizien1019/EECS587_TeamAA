#!/bin/bash
# The interpreter used to execute the script

#SBATCH --job-name=Darwin
#SBATCH --mail-user=zizien@umich.edu
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=500m
#SBATCH --time=00:10:00
#SBATCH --account=ywuocean0
#SBATCH --partition=standard

export LANG=en_US.utf8
export LC_ALL=en_US.utf8

module purge
module load gcc openmpi

g++ -std=c++11 -c  GraphHandler.cpp -o GraphHandler.o -I /home/zizien/Downloads/boost_1_82_0/out/include/
g++ -std=c++11 -c  Individual.cpp -o Individual.o -I /home/zizien/Downloads/boost_1_82_0/out/include/
g++ -std=c++11 -O0 -fopenmp InfectiousDiseaseModeling.cpp Individual.o GraphHandler.o -o main -I /home/zizien/Downloads/boost_1_82_0/out/include/
./main > output2

