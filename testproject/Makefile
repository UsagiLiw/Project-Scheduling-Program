# Makefile for Project Scheduling System project
# by: Bhimapaka Thapanangkun
# ID:60070503447

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= main$(EXECEXT)

all : $(EXECUTABLES)

linkedListQueue.o :	linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

linkedListGraph.o :	linkedListGraph.c abstractGraph.h abstractQueue.h projectInfo.h
	gcc -c linkedListGraph.c 

ioFunctions.o : ioFunctions.c ioFunctions.h
	gcc -c ioFunctions.c

writeFile.o : writeFile.c projectInfo.h abstractGraph.h
	gcc -c writeFile.c

fileLoader.o : fileLoader.c fileLoader.h projectInfo.h abstractGraph.h
	gcc -c fileLoader.c

loadFunctions.o : loadFunctions.c loadFunctions.h abstractGraph.h projectInfo.h
	gcc -c loadFunctions.c

createProject.o : createProject.c loadFunctions.h abstractGraph.h projectInfo.h ioFunctions.h
	gcc -c createProject.c

main.o : main.c fileLoader.h projectInfo.h abstractGraph.h
	gcc -c main.c

main$(EXECEXT) : main.o fileLoader.o linkedListGraph.o linkedListQueue.o loadFunctions.o writeFile.o createProject.o ioFunctions.o
	gcc -o main$(EXECEXT) main.o fileLoader.o linkedListGraph.o linkedListQueue.o loadFunctions.o writeFile.o createProject.o ioFunctions.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
