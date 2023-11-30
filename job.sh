#!/bin/bash
# The interpreter used to execute the script

#SBATCH --job-name=EE587
#SBATCH --mail-user=zizien@umich.edu
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=10g
#SBATCH --time=00:01:00
#SBATCH --account=ywuocean0
#SBATCH --partition=standard

export LANG=en_US.utf8
export LC_ALL=en_US.utf8

module purge
module load gcc openmpi

cd ~/EECS587_TeamAA

g++ -std=c++11 -c  GraphHandler.cpp -o GraphHandler.o -I /home/zizien/Downloads/boost_1_82_0/out/include/
g++ -std=c++11 -c  Individual.cpp -o Individual.o -I /home/zizien/Downloads/boost_1_82_0/out/include/
g++ -std=c++11 -O0 -fopenmp Infect.cpp Individual.o GraphHandler.o -o main -I /home/zizien/Downloads/boost_1_82_0/out/include/

./main > slurm999999999999999

