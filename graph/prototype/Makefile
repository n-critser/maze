CC=gcc
CFLAGS=-Wall -g3  
DEPS=graph.h mazeSearch.h

%.o: %.c $(DEPS)
	$(CC) -c -o  $@ $< $(CFLAGS)

#mazeSearchUnitTest : mazeSearchUnitTest.o
#	gcc -o mazeSearchUnitTest mazeSearchUnitTest.o $(CFLAGS) $(DEPS)



mzsTest : mazeSearchUnitTest.o graph.o mazeSearch.o
	$(CC) $(CFLAGS) -o mzsTest  mazeSearchUnitTest.o graph.o mazeSearch.o
