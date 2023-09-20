all: minHeap charHeap pokemon
	g++ -Wall -Werror -g minHeap.o charHeap.o assignment.o -o assignment -lncurses

pokemon: assignment.cpp minHeap
	g++ -g assignment.cpp -c

minHeap: minHeap.c minHeap.h
	g++ -g minHeap.c -c

charHeap: charHeap.c charHeap.h
	g++ -g charHeap.c -c

clean: 
	rm -f assignment.o minHeap.o charHeap.o pokemon