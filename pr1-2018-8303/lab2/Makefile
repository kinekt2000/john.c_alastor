C=gcc -c

all: index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o menu.o
	gcc index_first_zero.o index_last_zero.o sum_between.o sum_before_and_after.o menu.o -o menu

index_first_zero.o: index_first_zero.c
	$(C) index_first_zero.c

index_last_zero.o: index_last_zero.c
	$(C) index_last_zero.c

sum_between.o: sum_between.c
	$(C) sum_between.c

sum_before_and_after.o: sum_before_and_after.c
	$(C) sum_before_and_after.c

menu.o: menu.c
	$(C) menu.c

clean:                                                                          
	rm -rf *.o menu
