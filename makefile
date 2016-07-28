# simple make file
# September 2004
SOURCES=timeAverage.c 
PRODUCT=$(HOME)/bin/timeAverage



CC=gcc
CFLAGS=-lm -O2 -Wall #-I$(NR)/include

all: $(PRODUCT)

$(PRODUCT) : $(SOURCES)
	$(CC) $(CFLAGS) -o $(PRODUCT) $(SOURCES)


