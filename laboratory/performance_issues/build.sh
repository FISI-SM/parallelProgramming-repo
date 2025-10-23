#!/bin/bash

gcc -Wall -O0 01.c -o 01
gcc -Wall -O0 01-a.c -o 01-a

gcc -Wall -O0 02.c -o 02
gcc -Wall -O0 02-a.c -o 02-a

gcc -Wall -O0 03.c -o 03 -lpthread
gcc -Wall -O0 03-a.c -o 03-a -lpthread

gcc -Wall -O3 04.c -o 04
gcc -Wall -O3 04-a.c -o 04-a

gcc -Wall -O3 -fno-tree-vectorize 05.c -o 05
gcc -Wall -O3 -fno-tree-vectorize 05-a.c -o 05-a
