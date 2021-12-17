all: stringProg
	gcc -Wall -g -o stringProg stringProg.o
stringProg.o: stringProg.c
	gcc -Wall -g -c stringProg.c stringProg.h
PHONY: clean all
clean:
	rm -f *.out *.o stringProg stringProg.h.gch