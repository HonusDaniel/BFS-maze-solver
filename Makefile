OBJS	= main.o maze.o
SOURCE	= main.cpp maze.cpp
HEADER	= maze.h
OUT	= maze-solver
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

maze.o: maze.cpp
	$(CC) $(FLAGS) maze.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)
