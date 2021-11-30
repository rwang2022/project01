all: arg.o main.o
	gcc -o veryCoolShell main.o arg.o

main.o: main.c arg.h main.h palette.h
	gcc -c main.c

arg.o: arg.c arg.h palette.h
	gcc -c arg.c

clean:
	rm *.o
	rm veryCoolShell
	rm mom

run:
	./veryCoolShell