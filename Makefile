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

fileManagement.o : fileManagement.c fileManagement.h
	gcc -c fileManagement.c

main.o : main.c fileManagement.h
	gcc -c main.c

main$(EXECEXT) : main.o fileManagement.o 
	gcc -o main$(EXECEXT) main.o fileManagement.o 

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
