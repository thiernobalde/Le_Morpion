#* ******************************************************************
#* Polytech-marseille 												*
#* Projet d'algorithmique 2012-2013								 	*
#* Jeu du morpion													*
#* Baldé thierno et Pierre-martin Ekomo Abessolo					*
#********************************************************************

# Makefile du morpion - 27/12/2012

SHELL  = /bin/bash
CC     = gcc
RM     = rm -f
CFLAGS = `pkg-config gtk+-2.0 --cflags` -W -Wall -ansi -pedantic -g
LIBS   = `pkg-config gtk+-2.0 --libs`
MKDEP  = gcc -MM $(CFLAGS)

OBJECTS =  evaluation.o util.o morpion.o
EXEC    = prog

.c.o :
	$(CC) $(CFLAGS) -c $*.c

all :: $(EXEC)

$(EXEC) : $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

clean ::
	@ $(RM) *.o $(EXEC)

#depend ::
#	$(MKDEP) *.c > .depend

#include .depend
