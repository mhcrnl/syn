CC=gcc
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
CFLAGS=-Wall -Wextra -std=gnu11 -DDEBUG
LIBS=-luv

linux : $(OBJECTS)
	$(CC) -o syn $(CFLAGS) $(OBJECTS) $(LIBS) -lncurses 

other : $(OBJECTS)
	$(CC) -o syn $(CFLAGS) $(OBJECTS) $(LIBS)

all : $(OBJECTS)
	$(CC) -o syn $(CFLAGS) $(OBJECTS) $(LIBS) -lncurses

run:
	./syn
clean : 
	rm -f $(OBJECTS) syn
