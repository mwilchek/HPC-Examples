# Copyright (C) 2010 Glen Alan MacLachlan

CC=gcc
CFLAGS=  -Wall -g -ansi -std=c99 -fopenmp -O0
CMATH=-lm 
INCLUDE=-I ./include
SRC=src
OBJECTS= usage.o get_data.o  
EXE=get_stats


all: get_data usage get_stats 

get_stats: 
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(SRC)/$(EXE).c -o $(EXE) $(CMATH)

get_data:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)/get_data.c -c

usage: 
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)/usage.c -c


clean:
	rm $(OBJECTS) $(EXE) 

clean_objects:
	rm $(OBJECTS)
