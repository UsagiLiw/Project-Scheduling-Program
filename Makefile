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

fileLoader.o : fileLoader.c fileLoader.h projectInfo.h
	gcc -c fileLoader.c

main.o : main.c fileLoader.h projectInfo.h
	gcc -c main.c

main$(EXECEXT) : main.o fileLoader.o 
	gcc -o main$(EXECEXT) main.o fileLoader.o 

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
