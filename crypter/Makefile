.PHONY: all clean
all: decrypt encrypt test
clean:
	rm -f main.o crypto.o decrypt encrypt test
main.o: main.c
	gcc -Wall -c main.c
crypto.o: crypto.c
	gcc -Wall -c crypto.c
test.o: test.c
	gcc -Wall -c test.c
decrypt: main.o crypto.o
	gcc -o decrypt main.o crypto.o
encrypt: main.o crypto.o
	gcc -o encrypt main.o crypto.o
test: test.o crypto.o
	gcc -o test test.o crypto.o
