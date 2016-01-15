EXE=Maze
OBJECTS=main.o grid.o
CC=gcc 
FLAGS=-I./ -O3 -lrt -Wall

$(EXE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(EXE)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
