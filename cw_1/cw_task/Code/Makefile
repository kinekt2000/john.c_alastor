all: start
	./start

start: main.o text.o sentence.o
	gcc -Wall main.o text.o sentence.o -o start

main.o: main.c text.h sentence.h
	gcc -c main.c

text.o: text.c text.h sentence.h
	gcc -c text.c

sentence.o: sentence.c sentence.h
	gcc -c sentence.c

clean:
	rm -rf *.o start
