EXE=mod_queue
OBJECTS=test_mod_queue.o
CC=gcc 
FLAGS=-I./ -O3 -lrt -Wall -g

$(EXE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(EXE)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
