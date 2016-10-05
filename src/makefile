SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
CFLAGS=-Wall -Wextra -std=gnu11 -DDEBUG
LIBS=-luv -lrt -ldl
all : $(OBJECTS)
	$(CC) -o syn $(CFLAGS) $(OBJECTS) $(LIBS) 
run:
	./syn
clean : 
	rm -f $(OBJECTS) syn
