all: stringProg.o
	gcc -Wall -g -o stringProg stringProg.o
stringProg.o: stringProg.c stringProg.h
	gcc -Wall -g -c stringProg.c stringProg.h
clean:
	rm -f *.out *.o stringProg