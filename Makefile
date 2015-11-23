EXE=Maze
OBJECTS=main.o maze.o
CC=gcc
FLAGS=-I./ -O3 -lrt

$(EXE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(EXE)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
