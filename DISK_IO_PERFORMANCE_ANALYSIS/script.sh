#!/bin/bash

g++ -O3 part_one.cpp -o run
./run test.txt -w 1000000 10
./run test.txt -r 1000000 11
sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
g++ -O3 part_two.cpp -o run
./run small.txt 64
sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
g++ -O3  part_two_gb.cpp -o run -lbenchmark -lpthread
./run
sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
g++ -O3  part_three.cpp -o run 
./run small.txt 64000
sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
g++ -O3  part_four.cpp -o run 
./run small.txt 64000 y
./run small.txt 64000 n


g++ -O3  part_five.cpp -o run 
./run test.txt 1



