OBJS	= main.o maze.o
SOURCE	= main.c maze.cpp
HEADER	= maze.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c++11

maze.o: maze.cpp
	$(CC) $(FLAGS) maze.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)

