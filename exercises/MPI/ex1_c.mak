# 
CC 	=	mpicc

all:  ex1_solved.exe 

ex1_solved.exe:	ex1_solved.c
	$(CC) ex1_solved.c -o ex1_solved.exe -lm

clean:
	del /Q *.obj *.exe
