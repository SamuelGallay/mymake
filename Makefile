mymake: main.o
	gcc main.o -o mymake

main.o: main.c
	gcc -c main.c
