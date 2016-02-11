EXE=Maze
OBJECTS=main.o ../graph/grid.o mazeFace.o ioController.o
CURSES_MAZE=curses_maze.o
CC=gcc 
FLAGS=-I./ -O3 -lrt -Wall -lncurses
CURSOR=curse


$(EXE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(EXE)

$(CURSOR): $(CURSES_MAZE)
	$(CC) $(FLAGS) $(CURSES_MAZE)  -o $(CURSOR)


%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(EXE) $(CURSOR)
