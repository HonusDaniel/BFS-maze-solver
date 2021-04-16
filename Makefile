OBJS	= main.o maze.o
SOURCE	= main.c maze.c
HEADER	= maze.h
OUT	= maze
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

maze.o: maze.c
	$(CC) $(FLAGS) maze.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)
