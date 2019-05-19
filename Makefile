CC=g++
CFLAGS=-fno-rtti
CXXFLAGS=-Wall
DEPS = Snake.h Board.h
LIBS=-lncurses
OBJ=Snake.o Board.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(CXXFLAGS)

all: Main.cpp $(OBJ)
	$(CC) -o bin/snake $^  $(LIBS) $(CFLAGS) $(CXXFLAGS)
	
.PHONY: clean

clean:
	rm -f *.o bin/*
