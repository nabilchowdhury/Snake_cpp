CC=g++
CFLAGS=-fno-rtti
CXXFLAGS=-Wall
SRCS=Main.cpp Snake.cpp Board.cpp
LIBS=-lncurses


snake: Main.cpp Snake.cpp Board.cpp
	$(CC) -o bin/snake $(SRCS) $(LIBS)
