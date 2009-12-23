all: first remote-first HelloX
first: first.c
	gcc -o first first.c -lX11
remote-first: remote-first.c
	gcc -o remote-first remote-first.c -lX11
HelloX: HelloX.o
	gcc -o HelloX HelloX.o -Wall -L/usr/X11R6/lib -lX11

HelloX.o: HelloX.c
	gcc -o HelloX.o HelloX.c -c -ansi -pedantic -Wall

clean:
	rm -fr HelloX.o HelloX remote-first first

