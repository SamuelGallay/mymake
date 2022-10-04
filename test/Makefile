main: main.o a.o b.o c.o d.o
	gcc main.o a.o b.o c.o d.o -o main

main.o: main.c c.o c.h d.o d.h
	gcc -c main.c

a.o: a.c a.h
	gcc -c a.c

b.o: b.c b.h
	gcc -c b.c

c.o: c.c c.h a.o a.h b.o b.h
	gcc -c c.c

d.o: d.c d.h a.o a.h
	gcc -c d.c

