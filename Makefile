mymake: main.o rules.o parser.o rules.h parser.h
	gcc main.o rules.o parser.o -o mymake

main.o: main.c rules.h parser.h
	gcc -c main.c

rules.o: rules.c rules.h
	gcc -c rules.c

parser.o: parser.c parser.h rules.h 
	gcc -c parser.c
