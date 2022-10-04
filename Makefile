mymake: main.o regle.o regle.h
	gcc main.o regle.o -o mymake

main.o: main.c
	gcc -c main.c

regle.o: regle.c regle.h
	gcc -c regle.c
