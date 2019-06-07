all: start
	./start

start: main.o input.o
	gcc main.o input.o -o start

main.o: main.c input.h
	gcc -c main.c

input.o: input.c input.h
	gcc -c input.c

clean:
	rm -rf *.o start
