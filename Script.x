#!/bin/bash

rm saida.txt
make clean
make 

for i in $(seq 1 1 6);
do 
	echo "$i " >> saida.txt
	mpirun -np $i ./prog1 >> saida.txt
done 

