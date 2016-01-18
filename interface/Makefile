EXE=Maze
OBJECTS=main.o ../graph/grid.o
KEY_USE=key_use.o
CC=gcc 
FLAGS=-I./ -O3 -lrt -Wall -lncurses
CURSOR=curse

$(EXE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(EXE)

$(CURSOR): $(KEY_USE)
	$(CC) $(FLAGS) $(KEY_USE)  -o $(CURSOR)


%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(EXE) $(CURSOR)
